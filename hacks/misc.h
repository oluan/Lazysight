#pragma once

namespace misc
{
	
	static void weapon_recoil()
	{
		const auto plocal_actor = *reinterpret_cast<CActor**>(ironsight_base + 0xA88B34);
		if( plocal_actor )
		{
			plocal_actor->m_pweaponinfo->m_recoil = 0.0f;
		}
	}
	static void weapon_spread()
	{
		const auto plocal_actor = *reinterpret_cast<CActor**>(ironsight_base + 0xA88B34);
		if ( plocal_actor )
		{
			plocal_actor->m_pweaponinfo->m_spread = 0.0f;
		}
	}
	static void misc_context()
	{
		if ( config::b_recoil )
		{
			weapon_recoil();
		}

		if ( config::b_spread )
		{
			weapon_spread();
		}
		if( config::b_stamina )
		{
			const auto plocal_actor = *reinterpret_cast<CActor**>(ironsight_base + 0xA88B34);
			if (plocal_actor)
			{
				plocal_actor->m_max_stamina = 999999;
				plocal_actor->m_stamina = 999999;
			}
		}
		if( config::b_speed )
		{
			const auto plocal_actor = *reinterpret_cast<CActor**>(ironsight_base + 0xA88B34);
			if (plocal_actor)
			{
				plocal_actor->m_speed_running = 780.000f * (float)config::i_speed;
				plocal_actor->m_speed_forward = 520.000f * (float)config::i_speed;
				plocal_actor->m_speed_rightleft = 416.000f * (float)config::i_speed;
				plocal_actor->m_speed_back = 364.000f * (float)config::i_speed;
				plocal_actor->m_speed_scope = 0.500f * (float)config::i_speed;
				plocal_actor->m_speed_forward_down = 312.000f * (float)config::i_speed;
				plocal_actor->m_speed_rightleft_down = 249.000f * (float)config::i_speed;
				plocal_actor->m_speed_back_down = 218.000f * (float)config::i_speed;
				plocal_actor->m_speed_scope_down = 0.500f * (float)config::i_speed;
			}
		}
	}
}