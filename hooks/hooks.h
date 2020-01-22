#pragma once
#include <d3d9.h>
#include <mutex>
#include "../thirdparty/imgui/imgui.h"
#include "../thirdparty/imgui/imgui_impl_win32.h"
#include "../thirdparty/imgui/imgui_impl_dx9.h"

WNDPROC o_wndproc = nullptr;
bool b_render_menu = false;

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
		ImGui::CreateContext();
		ImGui_ImplWin32_Init( s_hwnd );
		ImGui_ImplDX9_Init( p_device );
	} );

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if ( b_render_menu )
	{
		if ( ImGui::Begin( "Lazysight", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse ) )
		{
			ImGui::Text( "Hello, world :p" );
			ImGui::End();
		}
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

	return o_present( p_device, p_src_rect, p_dest_rect, h_dest_window, p_dirty_region );
}