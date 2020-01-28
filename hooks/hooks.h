#pragma once
#include <d3d9.h>
#include <mutex>
#include "../thirdparty/imgui/imgui.h"
#include "../thirdparty/imgui/imgui_impl_win32.h"
#include "../thirdparty/imgui/imgui_impl_dx9.h"
#include <d3dx9.h>
#pragma comment(lib,"d3dx9.lib")


#include "../ironsight/sdk.h"
#include "../hacks/esp.h"
#include "../hacks/aimbot.h"
#include "../hacks/misc.h"
#include "../menu/menu.h"

WNDPROC o_wndproc = nullptr;
HWND g_hwnd = nullptr;
bool b_render_menu = false;

LRESULT wnd_proc( const HWND hwnd, const UINT u_msg, const WPARAM w_param, const LPARAM l_param )
{
	extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND, UINT, WPARAM, LPARAM );

	if ( u_msg == WM_KEYUP && w_param == VK_INSERT )
		b_render_menu = !b_render_menu;

	if ( b_render_menu && ImGui_ImplWin32_WndProcHandler( hwnd, u_msg, w_param, l_param ) )
		return 1l;

	return CallWindowProc( o_wndproc, hwnd, u_msg, w_param, l_param );
}

using fn_present = long( __stdcall* )( IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA* );
fn_present o_present = nullptr;

using sub_C6FFB0 = char( _fastcall* )(void* ecx, DWORD * p_this, int a2, float* a3);
sub_C6FFB0 o_sub_C6FFB0 = nullptr;

using sub_E001D0 = char( _fastcall* )(void *ecx, DWORD * p_this, int a2, bool* a3);
sub_E001D0 o_sub_E001D0 = nullptr;

long __stdcall hk_present( IDirect3DDevice9* p_device, const RECT* p_src_rect, const RECT* p_dest_rect, HWND h_dest_window, const RGNDATA* p_dirty_region )
{
	static std::once_flag o_flag;
	std::call_once( o_flag, [p_device]()
	{
		g_hwnd = FindWindow( nullptr, TEXT( "ironsight - 1.4.383.63755" ) );
		o_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( g_hwnd, GWLP_WNDPROC, LONG_PTR( wnd_proc ) ) );
		extern D3DVIEWPORT9 g_view_port;
		p_device->GetViewport( &g_view_port );
		ImGui::CreateContext();
		ImGui_ImplWin32_Init( g_hwnd );
		ImGui_ImplDX9_Init( p_device );
		menu::setup_style();
	});

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	menu::render();

	if ( config::visuals_toggle )
	{	
		render::start();

		// g_entity_manager 8B 0D ? ? ? ? 85 C9 74 15 83 C8 FF F0 0F C1 41 ? 48 75 0A 85 C9 74 06 8B 01 6A 01 FF 10 E8 ? ? ? ? 
		auto pentity_mgr = *reinterpret_cast< CEntityManager** >( ironsight_base + 0xA88B30 );

		if ( pentity_mgr )
		{
			// g_local_actor -> g_entity_manager + 0x4
			const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );
			const auto pentity_list = pentity_mgr->m_list;

			if ( pentity_list )
			{
				auto pentity_node = pentity_list->m_head;

				if ( pentity_node )
				{
					__try
					{
						while ( pentity_node != reinterpret_cast< CEntityNode* >( pentity_list ) )
						{
							auto pentity = pentity_node->m_instance;

							if ( pentity != plocal_actor && pentity->m_vtable_ptr == plocal_actor->m_vtable_ptr &&
								pentity->is_alive() )
							{
								const auto b_isenemy = pentity->m_teamid != plocal_actor->m_teamid;

								esp::line_esp( pentity, b_isenemy );
								esp::box2d( pentity, b_isenemy );
								esp::name_esp( pentity, b_isenemy );
							}

							pentity_node = pentity_node->m_next;
						}
					}

					__except ( EXCEPTION_EXECUTE_HANDLER )
					{
						//nothing here
					}
				}
			}
		}
		
		if ( config::b_view_fov )
			aimbot::fov( ImVec2( ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 ), config::i_fov * 6.2832 , config::view_fov );

		if( config::b_aimbot )
			aimbot::aimbot();

		if( config::b_trigger )
		{
			const auto plocal_actor = *reinterpret_cast<CActor**>( ironsight_base + 0xA88B34 );
			const auto ptrigger = reinterpret_cast<uintptr_t*>( ironsight_base + 0xA906CD );
			if( plocal_actor )
			{
				if (*reinterpret_cast<BYTE*>( ptrigger ))
				{
					plocal_actor->m_attacking = true;
				}
			}
		}
		
		render::end();
	}

	misc::misc_context();
	
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

	return o_present( p_device, p_src_rect, p_dest_rect, h_dest_window, p_dirty_region );
}

namespace Hook
{

	struct cHook
	{
		int temp = 0;
		void* address;
		void* hook;
		char api_bytes[13];
		unsigned char jmp[13];
		BYTE hook_func_legal1[6] = { 0x56 , 0x8B , 0xF1 , 0x8B , 0x4E , 0x04 };
		BYTE hook_func_legal2[7] = { 0x51 , 0x56 , 0xBE , 0x01 , 0x00 , 0x00 , 0x00 };
		void* api_function = VirtualAlloc(nullptr, 32, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	} hook;

	PBYTE Initialize(cHook* hook, void* rva, void* my_function, LPCSTR function_name, const UINT size_bytes, BYTE bytes[])
	{
		if (*static_cast<BYTE*>(hook->api_function) != 0) //check if first call
			hook->api_function = static_cast<char*>(hook->api_function) + hook->temp; //Increase void* to next memcpy function
		if (hook->api_function == nullptr)
		{
			MessageBoxA(nullptr, "Initialize() falhou: VirtualAlloc retornou um ponteiro nulo!", function_name, MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		hook->address = rva;

		if (hook->address == nullptr)
		{
			MessageBoxA(nullptr, "Initialize() falhou: RVA retornou um ponteiro nulo!", function_name, MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		hook->jmp[0] = 0xE9;
		*reinterpret_cast<ULONG*>(&hook->jmp[1]) = reinterpret_cast<ULONG>(my_function) - reinterpret_cast<ULONG>(hook->
			address) - 5; // Nâo modificar
		for (auto i = 5; i < size_bytes; i++)
		{
			hook->jmp[i] = 0x90;
		}
		memcpy(hook->api_bytes, bytes, size_bytes);
		memcpy(hook->api_function, hook->api_bytes, size_bytes);
		const auto orig_func = reinterpret_cast<ULONG>(hook->api_function) + size_bytes;
		const auto func_addr = reinterpret_cast<ULONG>(hook->address) + size_bytes;
		*static_cast<LPBYTE>(static_cast<LPBYTE>(hook->api_function) + size_bytes) = 0xe9;
		*reinterpret_cast<PULONG>(static_cast<LPBYTE>(hook->api_function) + (size_bytes + 1)) = static_cast<ULONG>(
			func_addr) -
			static_cast<ULONG>(orig_func) - 5; // Nâo modificar
		DWORD op;
		VirtualProtect(hook->address, size_bytes, PAGE_EXECUTE_READWRITE, &op);
		memcpy(hook->address, hook->jmp, size_bytes);
		VirtualProtect(hook->address, size_bytes, op, &op);
		hook->temp = size_bytes + 5;
		return static_cast<BYTE*>(hook->api_function);
	}
}

char _fastcall my_sub_C6FFB0(void* ecx, DWORD* p_this, int a2, float* a3)
{
	printf("\nsub_C6FFB0: %s", (char*)a2);
	return o_sub_C6FFB0(ecx, p_this, a2, a3);
}
char _fastcall my_sub_E001D0(void* ecx, DWORD * p_this, int a2, bool* a3)
{
	printf("\nsub_E001D0: %s", (char*)a2);
	return o_sub_E001D0(ecx, p_this, a2, a3);
}