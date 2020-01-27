#pragma once
#include "../ironsight/sdk.h"

namespace aimbot
{
	static CActor* get_nearest_entity( const CActor* plocal_actor )
	{	
		if ( !plocal_actor )
			return nullptr;

		CActor* pnearest_entity = nullptr;
		float   lowest_distance = 999999.0f;

		// g_entity_manager 8B 0D ? ? ? ? 85 C9 74 15 83 C8 FF F0 0F C1 41 ? 48 75 0A 85 C9 74 06 8B 01 6A 01 FF 10 E8 ? ? ? ? 
		auto pentity_mgr = *reinterpret_cast< CEntityManager** >( ironsight_base + 0xA88B30 );

		if ( pentity_mgr )
		{
			__try
			{
				const auto pentity_list = pentity_mgr->m_list;

				if ( pentity_list )
				{
					auto pentity_node = pentity_list->m_head;

					if ( pentity_node )
					{
						while ( pentity_node != reinterpret_cast< CEntityNode* >( pentity_list ) )
						{
							auto pentity = pentity_node->m_instance;

							if ( pentity != plocal_actor && pentity->m_vtable_ptr == plocal_actor->m_vtable_ptr &&
								pentity->is_alive() && pentity->m_teamid != plocal_actor->m_teamid )
							{
								auto distance = plocal_actor->m_head_coords.get_3d_distance( pentity->m_head_coords );

								if ( distance < lowest_distance )
								{
									lowest_distance = distance;
									pnearest_entity = pentity;
								}
							}

							pentity_node = pentity_node->m_next;
						}
					}
				}
			}

			__except ( EXCEPTION_EXECUTE_HANDLER )
			{
				return nullptr;
			}
		}

		return pnearest_entity;
	}

	static void aimbot() noexcept
	{
		ImGuiIO& io = ImGui::GetIO();

		//g_local_actor -> g_entity_manager + 0x4
		if ( io.MouseDownDuration[0] > 0.0f )
		{
			const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );
			const auto ptarget      = get_nearest_entity( plocal_actor );

			if ( !ptarget )
				return;

			const auto distance_x = plocal_actor->m_head_coords.get_distance_x( ptarget->m_head_coords );
			const auto distance_y = plocal_actor->m_head_coords.get_distance_y( ptarget->m_head_coords );
			const auto distance_z = plocal_actor->m_head_coords.get_distance_z( ptarget->m_head_coords );
			const auto distance   = plocal_actor->m_head_coords.get_3d_distance( ptarget->m_head_coords );

			float y = 0.0f;

			if ( ptarget->m_head_coords.x < plocal_actor->m_head_coords.x &&
				ptarget->m_head_coords.z > plocal_actor->m_head_coords.z )
			{
				y = ( atanf( abs( distance_x / distance_z ) ) / PI ) * 180.0f;
			}

			else if ( ptarget->m_head_coords.x > plocal_actor->m_head_coords.x&&
				ptarget->m_head_coords.z > plocal_actor->m_head_coords.z )
			{
				y = ( ( atanf( abs( distance_x / distance_z ) ) / PI ) * 180.0f ) * -1.0f;
			}

			else if ( ptarget->m_head_coords.x > plocal_actor->m_head_coords.x&&
				ptarget->m_head_coords.z < plocal_actor->m_head_coords.z )
			{
				y = ( ( atanf( abs( distance_x / distance_z ) ) / PI ) * 180.0f ) + 180.0f;
			}

			else if ( ptarget->m_head_coords.x < plocal_actor->m_head_coords.x &&
				ptarget->m_head_coords.z < plocal_actor->m_head_coords.z )
			{
				y = 180.0f - ( ( atanf( abs( distance_x / distance_z ) ) / PI ) * 180.0f );
			}

			const auto x = ( ( -asinf( distance_y / distance ) / PI ) * 180.0f ) - 0.2f;

			if ( config::b_smooth )
			{
				plocal_actor->m_view_angles.x += ( x - plocal_actor->m_view_angles.x ) / static_cast< float >( config::i_smooth );
				plocal_actor->m_view_angles.y += ( y - plocal_actor->m_view_angles.y ) / static_cast< float >( config::i_smooth );
			}

			else
			{
				plocal_actor->m_view_angles.x = x;
				plocal_actor->m_view_angles.y = y;
			}
		}
	}

	static void fov( const ImVec2 position, const int radius, float* color ) noexcept
	{
		render::circle( position, static_cast< float >( radius ), color );
	}
}