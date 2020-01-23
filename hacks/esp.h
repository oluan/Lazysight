#pragma once
#include "../ironsight/sdk.h"
#include "../render/render.h"
#include "../config/config.h"

namespace esp
{
	static void line_esp( CActor* pentity , bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_line ) return;
		if ( !is_enemy && !config::b_ally_line ) return;

		D3DXVECTOR2 screen{};

		if ( !sdk::world_to_screen( pentity->m_coordinates , screen ) )
			return;

		
		const auto p_vtable = pentity->m_vtable_ptr;

		// TEMPORARY CODE FOR DEBUGGING FIXME
		if ( *(DWORD*)p_vtable - ironsight_base == 0x296a10 )
		{
		/*	char buffer[255];
			sprintf_s( buffer, "~le object" );
			render::draw_text( buffer , ImVec2(screen.x, screen.y) , 15.f , config::ally_line );*/
			return;
		}
		render::draw_line( { ImGui::GetIO().DisplaySize.x / 2 , ImGui::GetIO().DisplaySize.y }, screen , is_enemy ? config::enemy_line : config::ally_line );
	}

	static void box2d( CActor* pentity , bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_box ) return;
		if ( !is_enemy && !config::b_ally_box ) return;

		Vector3 screen_head, screen_foot;
        const auto world_head = pentity->m_head_coords;
        const auto world_foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( world_head , screen_head ) || !sdk::world_to_screen( world_foot, screen_foot ) )
			return;

		screen_head.y -= 10;
		const auto y = screen_head.y;
		const auto h = screen_foot.y - screen_head.y;
		const auto w = h * (45.0f / 80.0f);
		const auto x = screen_head.x - w / 2.0f;

		render::draw_box( x  , y , w , h , is_enemy ? config::enemy_box : config::ally_box );
	}

	static void name_esp( CActor* pentity , bool is_enemy ) noexcept
	{
		if ( pentity->m_name[0] == '\0' ) return;
		if ( is_enemy && !config::b_enemy_name ) return;
		if ( !is_enemy && !config::b_ally_name ) return;


		auto foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( foot ) )
			return;

		foot.y += 8;
		char buffer[255];
		sprintf_s( buffer, "%S", pentity->m_name );
		render::draw_text( buffer , ImVec2( foot.x , foot.y ) , 12.f , is_enemy ? config::enemy_name : config::ally_name );
	}
}