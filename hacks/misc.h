#pragma once

namespace misc
{
	
	static void weapon_recoil() noexcept
	{
		const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );

		if ( plocal_actor )
			plocal_actor->m_pweaponinfo->m_recoil = 0.0f;
	}

	static void weapon_spread() noexcept
	{
		const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );

		if ( plocal_actor )
			plocal_actor->m_pweaponinfo->m_spread = 0.0f;
	}

	static void weapon_fire() noexcept
	{
		const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );
		const auto ptrigger = reinterpret_cast< byte* >( ironsight_base + 0xA906CD );

		if ( plocal_actor )
		{
			if ( *ptrigger )
				plocal_actor->m_attacking = true;
		}
	}
	
	static void misc_context() noexcept
	{
		if  (config::b_trigger )
			weapon_fire();
		
		if ( config::b_recoil )
			weapon_recoil();

		if ( config::b_spread )
			weapon_spread();

		if ( config::b_stamina )
		{
			const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );

			if ( plocal_actor )
			{
				plocal_actor->m_max_stamina = 999999.0f;
				plocal_actor->m_stamina     = 999999.0f;
			}
		}

		if ( config::b_speed )
		{
			const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );

			if ( plocal_actor )
			{
				plocal_actor->m_speed_running         = 780.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_forward         = 520.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_rightleft       = 416.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_back            = 364.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_scope           = 0.500f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_forward_down    = 312.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_rightleft_down  = 249.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_back_down       = 218.000f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_scope_down      = 0.500f * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_forward_lying   = ( 78.000f * 2.0f ) * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_rightleft_lying = ( 62.000f * 2.0f ) * static_cast< float >( config::i_speed );
				plocal_actor->m_speed_back_lying      = ( 54.000f * 2.0f ) * static_cast< float >( config::i_speed );
				//plocal_actor->m_speed_rise            = 10000.0f; //220.000f
				//plocal_actor->m_speed_lie_down        = 10000.0f; //160.000f
				//plocal_actor->m_speed_squat_down      = 10000.0f; //240.000f
			}
		}
	}
}