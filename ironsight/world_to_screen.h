#pragma once

D3DVIEWPORT9 g_view_port;

namespace sdk
{


	static bool world_to_screen( Vector3 pos, Vector3& screen ) noexcept
	{
		static float view_matrix[16] = { 0 };

		// g_matrix 03 05 ? ? ? ? 50
		const auto matrix = *reinterpret_cast< D3DXMATRIX* >( *reinterpret_cast< uintptr_t* >( ironsight_base + 0xA91D10 ) );
		memcpy( &view_matrix, matrix, sizeof D3DXMATRIX );

		D3DXVECTOR4 clip_coords = { };
		clip_coords.x = pos.x * view_matrix[0] + pos.y * view_matrix[1] + pos.z * view_matrix[2] + view_matrix[3];
		clip_coords.y = pos.x * view_matrix[4] + pos.y * view_matrix[5] + pos.z * view_matrix[6] + view_matrix[7];
		clip_coords.z = pos.x * view_matrix[8] + pos.y * view_matrix[9] + pos.z * view_matrix[10] + view_matrix[11];
		clip_coords.w = pos.x * view_matrix[12] + pos.y * view_matrix[13] + pos.z * view_matrix[14] + view_matrix[15];

		if ( clip_coords.w < 0.1f )
			return false;

		D3DXVECTOR3 ndc = { };
		ndc.x = clip_coords.x / clip_coords.w;
		ndc.y = clip_coords.y / clip_coords.w;
		ndc.z = clip_coords.z / clip_coords.w;

		screen.x = ( g_view_port.Width / 2 * ndc.x ) + ( ndc.x + g_view_port.Width / 2 );
		screen.y = -( g_view_port.Height / 2 * ndc.y ) + ( ndc.y + g_view_port.Height / 2 );
		return true;
	}

	[[nodiscard]] static bool world_to_screen( Vector3 pos, D3DXVECTOR2& out )
	{
		Vector3 _out = { out.x , out.y , 0 };
		const auto b = world_to_screen( pos , _out );
		out.x = _out.x;
		out.y = _out.y;
		return b;
	}

	[[nodiscard]] static bool world_to_screen( Vector3& pos )
	{
		return world_to_screen( pos , pos );
	}
}