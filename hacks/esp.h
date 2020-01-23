#pragma once
#include "../ironsight/sdk.h"
#include "../render/render.h"
#include "../config/config.h"

namespace esp
{
	static void line_esp( CActor* pentity , bool is_enemy ) noexcept
	{
		D3DXVECTOR2 screen{};

		if ( !sdk::world_to_screen( pentity->m_coordinates , screen ) )
			return;

		render::draw_line( { ImGui::GetIO().DisplaySize.x / 2 , ImGui::GetIO().DisplaySize.y }, screen , is_enemy ? config::enemy_line : config::ally_line );
	}

	static void box2d( CActor* pentity , bool is_enemy ) noexcept
	{

        const auto world_head = pentity->m_head_coords;
        const auto world_foot = pentity->m_coordinates;

		// todo
	}
}