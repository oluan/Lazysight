#pragma once

namespace misc
{	
	static void weapon_recoil( CActor* const plocal_actor ) noexcept
	{
		if ( plocal_actor )
			plocal_actor->m_pweaponinfo->m_recoil = 0.0f;
	}

	static void weapon_spread( CActor* const plocal_actor ) noexcept
	{
		if ( plocal_actor )
			plocal_actor->m_pweaponinfo->m_spread = 0.0f;
	}

	static void weapon_fire( CActor* const plocal_actor ) noexcept
	{
		const auto ptrigger = reinterpret_cast< byte* >( ironsight_base + 0xA906CD );

		if ( plocal_actor )
		{
			if ( *ptrigger )
				plocal_actor->m_attacking = true;
		}
	}
	
	static void misc_context() noexcept
	{
		const auto plocal_actor = *reinterpret_cast< CActor** >( ironsight_base + 0xA88B34 );

		if ( !plocal_actor )
			return;

		if ( config::b_trigger )
			weapon_fire( plocal_actor );
		
		if ( config::b_recoil )
			weapon_recoil( plocal_actor );

		if ( config::b_spread )
			weapon_spread( plocal_actor );

		if ( config::b_stamina )
		{
			if ( plocal_actor )
			{
				plocal_actor->m_max_stamina = 999999.0f;
				plocal_actor->m_stamina     = 999999.0f;
			}
		}

		if ( config::b_speed )
		{
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
			}
		}
	}
}