#pragma once

class CWeaponInfo
{
public:
	char pad_0000[60]; //0x0000
	float m_max_increase_recoil; //0x003C
	char pad_0040[36]; //0x0040
	float m_recoil; //0x0064
	float m_recoil_tick; //0x0068
	char pad_006C[4]; //0x006C
	float m_spread; //0x0070
}; //Size: 0x0074