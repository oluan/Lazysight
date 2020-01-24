#pragma once

class CActor
{
public:
	void* m_vtable_ptr; //0x0000
	char pad_0004[4]; //0x0004
	Vector3 m_coordinates; //0x0008
	char pad_0014[12]; //0x0014
	D3DXVECTOR2 m_view_angles; //0x0020
	char pad_0028[12]; //0x0028
	D3DXVECTOR2 m_velocity; //0x0034
	char pad_003C[8]; //0x003C
	float m_health; //0x0044
	char pad_0048[12]; //0x0048
	Vector3 m_coordinates2; //0x0054
	char pad_0060[128]; //0x0060
	uint32_t m_movement_flags; //0x00E0
	char pad_00E4[4]; //0x00E4
	bool m_attacking; //0x00E8
	char pad_00E9[215]; //0x00E9
	float m_max_stamina; //0x01C0
	float m_stamina; //0x01C4
	char pad_01C8[224]; //0x01C8
	float m_speed_running; //0x02A8
	float m_speed_forward; //0x02AC
	float m_speed_rightleft; //0x02B0
	float m_speed_back; //0x02B4
	float m_speed_scope; //0x02B8
	char pad_02BC[4]; //0x02BC
	float m_speed_forward_down; //0x02C0
	float m_speed_rightleft_down; //0x02C4
	float m_speed_back_down; //0x02C8
	float m_speed_scope_down; //0x02CC
	char pad_02D0[152]; //0x02D0
	Vector3 m_head_coords; //0x0368
	char pad_0374[72]; //0x0374
	float m_camera_view; //0x03BC
	char pad_03C0[60]; //0x03C0
	class CWeaponManager* m_pweaponmgr; //0x03FC
	class CWeaponInfo* m_pweaponinfo; //0x0400
	char pad_0404[1060]; //0x0404
	wchar_t m_name[16]; //0x0828
	wchar_t m_clan_name[16]; //0x0848
	char pad_0868[96]; //0x0868
	uint8_t pad; //0x08C8
	uint8_t m_teamid; //0x08C9
	char pad_08CA[58]; //0x08CA
	float m_max_health; //0x0904
	inline bool is_alive() { return this->m_health > 0.0f; };
}; //Size: 0x08CA

