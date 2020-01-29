#include "config.h"

namespace config
{
	float enemy_line[3];
	float ally_line[3];
	float ally_box[3];
	float enemy_box[3];
	float ally_name[3];
	float enemy_name[3];
	float ally_distance[3];
    float enemy_distance[3];
	float ally_hp[3];
	float enemy_hp[3];
	float ally_hp_bar[3];
	float enemy_hp_bar[3];
	float view_fov[3];

	bool b_enemy_line;
	bool b_ally_line;
	bool b_enemy_box;
	bool b_ally_box;
	bool b_enemy_name;
	bool b_ally_name;
	bool b_enemy_distance;
	bool b_ally_distance;
	bool b_enemy_hp;
	bool b_ally_hp;
	bool b_enemy_hp_bar;
	bool b_ally_hp_bar;
	bool b_aimbot;
	bool b_view_fov;
	int i_fov = 30;
	bool b_trigger;
	bool b_smooth;
	int i_smooth;

	bool visuals_toggle;
	bool b_recoil;
	bool b_spread;
	bool b_stamina;
	bool b_speed;
	int i_speed = 1.0f;

	float f_accumulative;
}