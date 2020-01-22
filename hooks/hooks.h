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

WNDPROC o_wndproc = nullptr;
bool b_render_menu = false;

// temp
ID3DXLine* g_line = nullptr;
bool b_esp_line = false;


LRESULT wnd_proc( const HWND hwnd, const UINT u_msg, const WPARAM w_param, const LPARAM l_param )
{
	extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND, UINT, WPARAM, LPARAM );

	if ( u_msg == WM_KEYDOWN && w_param == VK_INSERT )
		b_render_menu = !b_render_menu;

	if ( ImGui_ImplWin32_WndProcHandler( hwnd, u_msg, w_param, l_param ) )
		return 1l;

	return CallWindowProc( o_wndproc, hwnd, u_msg, w_param, l_param );
}

using fn_present = long( __stdcall* )( IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA* );
fn_present o_present = nullptr;

long __stdcall hk_present( IDirect3DDevice9* p_device, const RECT* p_src_rect, const RECT* p_dest_rect, HWND h_dest_window, const RGNDATA* p_dirty_region )
{
	static std::once_flag o_flag;
	std::call_once( o_flag, [p_device]()
	{
		const auto s_hwnd = FindWindow( nullptr, TEXT( "ironsight - 1.4.383.63755" ) );
		o_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( s_hwnd, GWLP_WNDPROC, LONG_PTR( wnd_proc ) ) );
		extern D3DVIEWPORT9 g_view_port;
		p_device->GetViewport( &g_view_port );
		ImGui::CreateContext();
		ImGui_ImplWin32_Init( s_hwnd );
		ImGui_ImplDX9_Init( p_device );
		D3DXCreateLine( p_device, &g_line );
	} );

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if ( b_render_menu )
	{
		if ( ImGui::Begin( "Lazysight", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse ) )
		{
			ImGui::Checkbox( "ESP Line" , &b_esp_line );
			ImGui::End();
		}
	}

	static auto ironsight_base = 0;

	if ( !ironsight_base )
		ironsight_base = reinterpret_cast< uintptr_t >( GetModuleHandle( nullptr ) );

	if ( b_esp_line )
	{	
		// g_entity_manager 8B 0D ? ? ? ? 85 C9 74 15 83 C8 FF F0 0F C1 41 ? 48 75 0A 85 C9 74 06 8B 01 6A 01 FF 10 E8 ? ? ? ? 
		auto pentity_mgr = *reinterpret_cast< CEntityManager** >( ironsight_base + 0xA88B30 );

		if ( pentity_mgr )
		{
			//g_local_actor -> g_entity_manager + 0x4
			const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );
			const auto pentity_list = pentity_mgr->m_list;

			if ( pentity_list )
			{
				auto pentity_node = pentity_list->m_head;

				if ( pentity_node )
				{
					while ( pentity_node != reinterpret_cast< CEntityNode* >( pentity_list ) )
					{
						auto pentity = pentity_node->m_instance;

						if ( pentity != plocal_actor && pentity->m_teamid != plocal_actor->m_teamid )
							esp::line_esp( pentity );

						pentity_node = pentity_node->m_next;
					}
				}
			}
		}
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

	return o_present( p_device, p_src_rect, p_dest_rect, h_dest_window, p_dirty_region );
}