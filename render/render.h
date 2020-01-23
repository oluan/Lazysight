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

	static float draw_text( const std::string& text, const ImVec2& position, float size, float* color, bool center = true ) noexcept
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();


		std::stringstream stream(text);
		std::string line;

		float y = 0.0f;
		int i = 0;

		while ( std::getline( stream, line ) )
		{
			ImVec2 textSize = ImGui::GetDefaultFont()->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

			if (center)
			{
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 255 / 255.0f }), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 255 / 255.0f }), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 255 / 255.0f }), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 255 / 255.0f }), line.c_str());

				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { position.x - textSize.x / 2.0f, position.y + textSize.y * i }, ImGui::GetColorU32(color), line.c_str());
			}
			else
			{
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32(color), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32(color), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32(color), line.c_str());
				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { (position.x) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32(color), line.c_str());

				window->DrawList->AddText(ImGui::GetDefaultFont(), size, { position.x, position.y + textSize.y * i }, ImGui::GetColorU32(color), line.c_str());
			}

			y = position.y + textSize.y * (i + 1);
			i++;
		}

		return y;

	}
}