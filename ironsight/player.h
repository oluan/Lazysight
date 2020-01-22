#pragma once

class CPlayer
{
public:
	void* vtable_ptr; //0x0000
	char pad_0004[4]; //0x0004
	D3DXVECTOR3 m_coordinates; //0x0008
	char pad_0014[12]; //0x0014
	D3DXVECTOR2 m_view_angles; //0x0020
	char pad_0028[12]; //0x0028
	D3DXVECTOR2 m_velocity; //0x0034
	char pad_003C[8]; //0x003C
	float m_health; //0x0044
	char pad_0048[12]; //0x0048
	D3DXVECTOR3 m_coordinates2; //0x0054
	char pad_0060[344]; //0x0060
	uint32_t N000000C6; //0x01B8
	float random; //0x01BC
	float m_max_stamina; //0x01C0
	float m_stamina; //0x01C4
	char pad_01C8[192]; //0x01C8
	float N000000FA; //0x0288
	float N000000FB; //0x028C
	float N000000FC; //0x0290
	float N000000FD; //0x0294
	float N00000787; //0x0298
	float N000000FE; //0x029C
	float N000000FF; //0x02A0
	float N00000100; //0x02A4
	float N00000101; //0x02A8
	float N00000102; //0x02AC
	float N00000103; //0x02B0
	float N00000104; //0x02B4
	float N00000105; //0x02B8
	float N00000106; //0x02BC
	float N00000107; //0x02C0
	float N00000108; //0x02C4
	float N00000109; //0x02C8
	float N0000010A; //0x02CC
	float N0000010B; //0x02D0
	float N0000010C; //0x02D4
	float N0000010D; //0x02D8
	float N0000010E; //0x02DC
	float N0000010F; //0x02E0
	float N00000110; //0x02E4
	float N00000111; //0x02E8
	char pad_02EC[68]; //0x02EC
	D3DXMATRIX m_view_matrix; //0x0330
	char pad_0370[1208]; //0x0370
	wchar_t m_name[16]; //0x0828
	wchar_t m_clan_name[16]; //0x0848
}; //Size: 0x0868