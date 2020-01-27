#pragma once

#include "../thirdparty/imgui/imgui.h"
#include <d3dx9.h>
#include "../thirdparty/imgui/imgui_internal.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace render
{
	static void start() noexcept
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

		ImGui::Begin("##Canvas", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus );

	}

	static void end() noexcept
	{
		ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar( 2 );
	}

	static void draw_line( D3DXVECTOR2 from , D3DXVECTOR2 to , float* col , const bool outlined = true , const float thickness = 0.4f ) noexcept
	{
		if ( outlined )
		{
			// original pos backup
			const auto b_from = from, b_to = to;

			from.x += 1;
			from.y += 1;
			to.x += 1;
			to.y += 1;

			ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), thickness );

			from.x -= 2;
			to.x -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), thickness );

			from.x += 2;
			from.y -= 2;
			to.x += 2;
			to.y -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), thickness );

			from.x -= 2;
			to.x -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), thickness );

			from = b_from;
			to = b_to;


		}
		ImGui::GetCurrentWindow()->DrawList->AddLine( from , to , ImGui::GetColorU32( col ), thickness );
	}

	static float draw_text( const std::string& text, ImVec2 pos, float size, float* color, bool center = true ) noexcept
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();


		std::stringstream stream(text);
		std::string line;

		const auto text_size = ImGui::GetDefaultFont()->CalcTextSizeA(size, FLT_MAX, 0.0f, text.c_str());
		if (center)
			pos.x -= text_size.x / 2.0f;

		// outline
		window->DrawList->AddText(ImGui::GetDefaultFont(), size, ImVec2(pos.x + 1, pos.y + 1), ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), text.c_str());
		window->DrawList->AddText(ImGui::GetDefaultFont(), size, ImVec2(pos.x - 1, pos.y - 1), ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), text.c_str());
		window->DrawList->AddText(ImGui::GetDefaultFont(), size, ImVec2(pos.x + 1, pos.y - 1), ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), text.c_str());
		window->DrawList->AddText(ImGui::GetDefaultFont(), size, ImVec2(pos.x - 1, pos.y + 1), ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ), text.c_str());
		
		window->DrawList->AddText(ImGui::GetDefaultFont(), size, ImVec2(pos.x , pos.y ), ImGui::GetColorU32( color ), text.c_str());


		return pos.y + text_size.y;

	}

	static void draw_box( float x , float y, float w, float h, float* col , bool outlined = true , float thickness = 0.4f )
	{
		if ( outlined )
		{
			// original pos backup
			const auto b_x = x, b_y = y;

			x += 1;
			y += 1;

			ImGui::GetCurrentWindow()->DrawList->AddRect( ImVec2( x, y ) , ImVec2( x + w , y + h ) , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ) , 0.0f , 15 , thickness );

			x -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddRect( ImVec2( x, y ) , ImVec2( x + w , y + h ) , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ) , 0.0f , 15 , thickness );

			x += 2;
			y -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddRect( ImVec2( x, y ) , ImVec2( x + w , y + h ) , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ) , 0.0f , 15 , thickness );

			x -= 2;

			ImGui::GetCurrentWindow()->DrawList->AddRect( ImVec2( x, y ) , ImVec2( x + w , y + h ) , ImGui::GetColorU32( { 0 , 0 , 0 , 1 } ) , 0.0f , 15 , thickness );

			x = b_x;
			y = b_y;

		}
		ImGui::GetCurrentWindow()->DrawList->AddRect( ImVec2( x, y ) , ImVec2( x + w , y + h ) , ImGui::GetColorU32( col ) , 0.0f , 15 , thickness ) ;
	}

	static void circle( const ImVec2 position , const float radius , float* color , const float thickness = 0.4f )
	{
		ImGui::GetCurrentWindow()->DrawList->AddCircle( ImVec2( position.x , position.y ) , radius , ImGui::GetColorU32( color ) , 128 , thickness );
	}
}