#pragma once

#include "../thirdparty/imgui/imgui.h"
#include <d3dx9.h>
#include "../thirdparty/imgui/imgui_internal.h"

namespace render
{
	static void start() noexcept
	{
		ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
		ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f } );
		ImGui::PushStyleColor( ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f } );

		ImGui::SetNextWindowPos( ImVec2(0, 0), ImGuiCond_Always );
		ImGui::SetNextWindowSize( ImVec2( ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y ), ImGuiCond_Always );

		ImGui::Begin( "##Canvas", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs );

	}

	static void end() noexcept
	{
		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar( 2 );
	}

	static void draw_line( D3DXVECTOR2 from , D3DXVECTOR2 to , float* col , float thickness = 1.0f ) noexcept
	{
		ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( col ), thickness );
	}


}