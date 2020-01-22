#pragma once

class CWeaponManager
{
public:
	void* N00000781; //0x0000
	char pad_0004[40]; //0x0004
	float N0000078C; //0x002C
	float N0000078D; //0x0030
	float N0000078E; //0x0034
	char pad_0038[396]; //0x0038
	D3DXVECTOR2 m_angles; //0x01C4
	char pad_01CC[52]; //0x01CC
	bool m_zooming; //0x0200
	char pad_0201[55]; //0x0201
	bool m_shooting; //0x0238
	char pad_0239[67]; //0x0239
	uint32_t N00000823; //0x027C
	bool N00000824; //0x0280
	char pad_0281[135]; //0x0281
	uint32_t nlmao; //0x0308
	char pad_030C[8]; //0x030C
	uint32_t m_bullets; //0x0314
	uint32_t m_bullets2; //0x0318
	char pad_031C[60]; //0x031C
	D3DXVECTOR3 m_lasthit_coords; //0x0358
	char pad_0364[4]; //0x0364
	uint32_t m_currentslot; //0x0368
	char pad_036C[160]; //0x036C
	uint32_t m_slot1_ammo; //0x040C
	uint32_t m_slot1_ammo2; //0x0410
}; //Size: 0x102E