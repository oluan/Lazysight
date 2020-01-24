#pragma once

class CWeaponManager
{
public:
	char pad_0000[452]; //0x0000
	D3DXVECTOR2 m_angles; //0x01C4
	char pad_01CC[52]; //0x01CC
	bool m_zooming; //0x0200
	char pad_0201[55]; //0x0201
	bool m_shooting; //0x0238
	char pad_0239[219]; //0x0239
	uint32_t m_bullets; //0x0314
	uint32_t m_bullets2; //0x0318
	char pad_031C[60]; //0x031C
	Vector3 m_lasthit_coords; //0x0358
	char pad_0364[4]; //0x0364
	uint32_t m_currentslot; //0x0368
	char pad_036C[160]; //0x036C
	uint32_t m_slot1_ammo; //0x040C
	uint32_t m_slot1_ammo2; //0x0410
}; //Size: 0x0414