#pragma once
#include "../ironsight/sdk.h"
#include "../render/render.h"
#include "../config/config.h"

namespace esp
{
	static void line_esp( CActor* pentity, bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_line ) return;
		if ( !is_enemy && !config::b_ally_line ) return;

		D3DXVECTOR2 screen{ };

		if ( !sdk::world_to_screen( pentity->m_coordinates, screen ) )
			return;

		render::draw_line( { ImGui::GetIO().DisplaySize.x / 2 , ImGui::GetIO().DisplaySize.y }, screen, is_enemy ? config::enemy_line : config::ally_line );
	}

	static void box2d( CActor* pentity, bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_box ) return;
		if ( !is_enemy && !config::b_ally_box ) return;

		Vector3 screen_head, screen_foot;
		const auto world_head = pentity->m_head_coords;
		const auto world_foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( world_head, screen_head ) || !sdk::world_to_screen( world_foot, screen_foot ) )
			return;

		screen_head.y -= 10;
		const auto y = screen_head.y;
		const auto h = screen_foot.y - screen_head.y;
		const auto w = h * ( 45.0f / 80.0f );
		const auto x = screen_head.x - w / 2.0f;

		render::draw_box( x, y, w, h, is_enemy ? config::enemy_box : config::ally_box );
	}

	static void name_esp( CActor* pentity, bool is_enemy ) noexcept
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

		render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, is_enemy ? config::enemy_name : config::ally_name );
	}

	static void hp_text( CActor* pentity, bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_hp ) return;
		if ( !is_enemy && !config::b_ally_hp ) return;

		auto foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( foot ) )
			return;

		foot.y += 8;

		const auto hpmax = pentity->m_max_health;
		const auto hpnow = pentity->m_health;

		const auto percent = ( hpnow / hpmax ) * 100;

		char buffer[255];
		sprintf_s( buffer, "%u", static_cast< unsigned int >( percent ) );

		if ( percent == 100 )
		{
			float color[] = { 0.f , 174.f / 255.f , 12.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 80 )
		{
			float color[] = { 232.f / 255.f , 232.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 70 )
		{
			float color[] = { 232.f / 255.f , 191.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 50 )
		{
			float color[] = { 232.f / 255.f , 163.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 30 )
		{
			float color[] = { 232.f / 255.f , 136.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 20 )
		{
			float color[] = { 232.f / 255.f , 115.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else if ( percent > 10 )
		{
			float color[] = { 232.f / 255.f , 60.f / 255.f , 26.f / 255.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}

		else
		{
			float color[] = { 1.f , 0.f , 0.f };
			render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, color );
		}
	}

	static void hp_bar( CActor* pentity, const bool is_enemy ) noexcept
	{
		if ( is_enemy && !config::b_enemy_hp_bar ) return;
		if ( !is_enemy && !config::b_ally_hp_bar ) return;

		Vector3 screen_head, screen_foot;
		const auto world_head = pentity->m_head_coords;
		const auto world_foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( world_head, screen_head ) || !sdk::world_to_screen( world_foot, screen_foot ) )
			return;

		screen_head.y -= 10;

		const auto y = screen_head.y;
		const auto h = screen_foot.y - screen_head.y;
		const auto w = 3.0f;
		const auto x = screen_head.x - ( ( h * ( 45.0f / 80.0f ) ) / 2.0f ) - 5.0f;

		const auto hpmax = pentity->m_max_health;
		const auto hpnow = pentity->m_health;

		const auto percent = ( hpnow / hpmax ) * 100;
		const auto percent_h = percent * h / 100.0f;

		if ( percent == 100 )
		{
			float color[] = { 0.f , 174.f / 255.f , 12.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 80 )
		{
			float color[] = { 232.f / 255.f , 232.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 70 )
		{
			float color[] = { 232.f / 255.f , 191.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 50 )
		{
			float color[] = { 232.f / 255.f , 163.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 30 )
		{
			float color[] = { 232.f / 255.f , 136.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 20 )
		{
			float color[] = { 232.f / 255.f , 115.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else if ( percent > 10 )
		{
			float color[] = { 232.f / 255.f , 60.f / 255.f , 26.f / 255.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}

		else
		{
			float color[] = { 1.f , 0.f , 0.f };
			render::draw_bar( x, y, w, h, percent_h, is_enemy ? config::enemy_hp_bar : config::ally_hp_bar, color );
		}
	}

	static void distance_esp( CActor* pentity, const float distance, const bool is_distance ) noexcept
	{
		if ( is_distance && !config::b_enemy_distance ) return;
		if ( !is_distance && !config::b_ally_distance ) return;

		auto foot = pentity->m_coordinates;

		if ( !sdk::world_to_screen( foot ) )
			return;

		foot.y += 8;

		char buffer[255];
		sprintf_s( buffer, "%.2f", distance / 100.0f );

		render::draw_text( buffer, ImVec2( foot.x, foot.y ), 12.f, is_distance ? config::enemy_distance : config::ally_distance );
	}
}