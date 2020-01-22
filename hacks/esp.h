#pragma once
#include "../ironsight/sdk.h"

extern ID3DXLine* g_line;

namespace esp
{
	static void line_esp( CActor* pentity ) noexcept
	{
		// draw class WIP
		static D3DXVECTOR2 line_2d[2]{};

		D3DXVECTOR2 screen{};

		if ( !sdk::world_to_screen( pentity->m_head_coords , screen ) )
			return;

		g_line->SetWidth( 1.2f );
		g_line->SetAntialias( true );
		g_line->SetGLLines( true );

		line_2d[0].x = 0;
		line_2d[0].y = 0;

		line_2d[1].x = screen.x;
		line_2d[1].y = screen.y;

		g_line->Draw( line_2d, 2, D3DCOLOR_ARGB( 255, 0, 0, 0 ) );
	}
}