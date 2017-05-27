
#pragma once

#include <Common/Yacc/yywclex.h>
#include <map>
#include <vector>

class CLexerForSkill : public yl::yywflexer {
public:
	enum Token;

	static void Init();
	static void AddToken(const wchar_t *name, Token action, const Token type, const bool own);

	yl::yywint_t yyaction_(int action);

	class Subst {
	public:
		Token token;
		Token action;
		bool own;
	};

	static std::map<std::wstring, Subst> newTokens;
	static yl::yywint_t substAction;
	static bool substOwn;
	static int substActionState;

	enum Token {
		SEMICOLON = 59,
		LBRACKET = 123,
		RBRACKET = 125,
		ASSIGN = 65537,
		skill_begin = 65538,
		skill_name = 65539,
		is_magic = 65540,
		magic_level = 65541,
		skill_id = 65542,
		level = 65543,
		operate_type = 65544,
		mp_consume1 = 65545,
		mp_consume2 = 65546,
		mp_consume_tick = 65547,
		hp_consume = 65549,
		item_consume = 65550,
		effective_range = 65551,
		cast_range = 65552,
		skill_hit_time = 65553,
		skill_cool_time = 65554,
		skill_hit_cancel_time = 65555,
		reuse_delay = 65556,
		operate_cond = 65558,
		target_operate_cond = 65559,
		passive_conditions = 65560,
		activate_rate = 65561,
		lv_bonus_rate = 65562,
		basic_property = 65563,
		effect = 65564,
		start_effect = 65565,
		fail_effect = 65566,
		tick_effect = 65567,
		tick_interval = 65568,
		end_effect = 65569,
		self_effect = 65570,
		pvp_effect = 65571,
		pve_effect = 65572,
		attached_skill = 65573,
		abnormal_time = 65574,
		abnormal_lv = 65575,
		abnormal_type = 65576,
		effect_point = 65577,
		abnormal_visual_effect = 65578,
		multi_class = 65579,
		abnormal_instant = 65580,
		debuff = 65581,
		irreplaceable_buff = 65582,
		ride_state = 65583,
		target_type = 65584,
		affect_scope = 65585,
		affect_limit = 65586,
		affect_range = 65587,
		fan_range = 65588,
		affect_object = 65589,
		affect_scope_height = 65590,
		next_action = 65591,
		skill_end = 65592,
		reuse_delay_type = 65594,
		attribute = 65595,
		trait = 65596,
		reuse_delay_lock = 65597,
		consume_etc = 65598,
		buff_protect_level = 65599,
		abnormal_delete_leaveworld = 65600,
		transform_type = 65601,
		can_refuel_airship = 65606,
		can_bookmark_add_slot = 65607,
		can_add_max_entrance_inzone = 65608,
		op_skill = 65611,
		op_need_agathion = 65612,
		can_transform = 65613,
		can_untransform = 65614,
		cannot_use_in_transform = 65616,
		op_check_cast_range = 65618,
		op_check_abnormal = 65619,
		op_change_weapon = 65620,
		op_check_pcbang_point = 65621,
		equip_weapon = 65622,
		target_item_crystal_type = 65623,
		target_race = 65624,
		equip_shield = 65625,
		possess_holything = 65626,
		build_camp = 65627,
		build_advance_base = 65628,
		can_transform_in_dominion = 65629,
		remain_hp_per = 65630,
		remain_mp_per = 65631,
		remain_cp_per = 65632,
		target_my_party = 65633,
		target_my_pledge = 65634,
		consume_body = 65635,
		energy_saved = 65636,
		soul_saved = 65637,
		can_summon_pet = 65638,
		can_summon = 65639,
		can_summon_cubic = 65640,
		can_summon_siege_golem = 65641,
		op_sweeper = 65642,
		op_siege_hammer = 65643,
		op_resurrection = 65644,
		check_sex = 65646,
		check_level = 65647,
		op_energy_max = 65648,
		op_soul_max = 65649,
		op_home = 65650,
		op_wyvern = 65651,
		op_2h_weapon = 65652,
		op_unlock = 65653,
		op_companion = 65654,
		op_use_firecracker = 65655,
		op_fishing_cast = 65656,
		op_fishing_pumping = 65657,
		op_fishing_reeling = 65657,
		op_territory = 65659,
		op_not_territory = 65660,
		op_alignment = 65661,
		op_encumbered = 65662,
		op_call_pc = 65663,
		op_check_class = 65664,
		op_check_class_list = 65665,
		op_exist_npc = 65667,
		op_target_npc = 65669,
		op_can_escape = 65670,
		op_enchant_range = 65671,
		can_use_swoop_cannon = 65672,
		can_use_in_battlefield = 65673,
		can_enchant_attribute = 65674,
		op_check_flag = 65675,
		op_check_residence = 65677,
		op_blink = 65678,
		can_mount_for_event = 65679,
		i_refuel_airship = 65681,
		i_bookmark_add_slot = 65682,
		i_bookmark_teleport = 65683,
		i_add_max_entrance_inzone = 65684,
		i_summon_cubic = 65685,
		i_blink = 65686,
		i_steal_abnormal = 65687,
		i_m_attack_by_abnormal = 65688,
		i_focus_soul = 65689,
		i_remove_soul = 65690,
		i_summon_trap = 65691,
		i_detect_trap = 65692,
		i_defuse_trap = 65693,
		i_transfer_hate = 65694,
		i_call_skill = 65695,
		i_m_attack_by_range = 65696,
		i_summon_agathion = 65697,
		i_unsummon_agathion = 65698,
		i_dispel_by_name = 65701,
		i_dispel_by_slot = 65702,
		i_dispel_by_slot_myself = 65703,
		i_p_attack = 65704,
		i_p_soul_attack = 65705,
		i_fatal_blow = 65706,
		i_soul_blow = 65707,
		i_heal = 65708,
		i_hp_drain = 65709,
		i_m_attack = 65710,
		i_m_soul_attack = 65711,
		i_escape = 65712,
		i_hp = 65713,
		i_mp = 65714,
		i_resurrection = 65716,
		i_summon = 65717,
		i_dispel_by_category = 65718,
		i_enchant_armor = 65719,
		i_enchant_weapon = 65720,
		i_enchant_attribute = 65721,
		i_enchant_weapon_rate = 65722,
		i_enchant_armor_rate = 65723,
		i_hp_per_max = 65724,
		i_mp_per_max = 65725,
		i_mp_by_level = 65726,
		i_pcbang_point_up = 65727,
		i_add_hate = 65728,
		i_holything_possess = 65729,
		i_install_camp = 65730,
		i_unlock = 65731,
		i_delete_hate = 65732,
		i_randomize_hate = 65733,
		i_focus_energy = 65734,
		i_focus_max_energy = 65735,
		i_energy_attack = 65736,
		i_soul_shot = 65737,
		i_spirit_shot = 65738,
		i_summon_soul_shot = 65739,
		i_summon_spirit_shot = 65740,
		i_confuse = 65741,
		i_run_away = 65742,
		i_consume_body = 65743,
		i_hp_by_level_self = 65744,
		i_mp_by_level_self = 65745,
		i_spoil = 65746,
		i_sweeper = 65747,
		i_backstab = 65748,
		i_distrust = 65749,
		i_delete_hate_of_me = 65750,
		i_death_link = 65751,
		i_dispel_all = 65752,
		i_summon_pet = 65753,
		i_food_for_pet = 65754,
		i_fly_away = 65755,
		i_fly_self = 65756,
		i_register_siege_golem = 65757,
		i_m_attack_over_hit = 65758,
		i_restoration = 65759,
		i_restoration_random = 65760,
		i_sowing = 65761,
		i_harvesting = 65762,
		i_hp_self = 65763,
		i_give_contribution = 65764,
		i_change_face = 65765,
		i_change_hair_style = 65766,
		i_change_hair_color = 65767,
		i_summon_npc = 65768,
		i_cp = 65769,
		i_sp = 65770,
		i_physical_attack_hp_link = 65771,
		i_m_attack_by_dist = 65773,
		i_fishing_cast = 65774,
		i_fishing_pumping = 65775,
		i_fishing_reeling = 65776,
		i_fishing_shot = 65777,
		i_open_dwarf_recipebook = 65778,
		i_open_common_recipebook = 65779,
		i_abnormal_time_change = 65780,
		i_dispel_by_slot_probability = 65781,
		i_align_direction = 65782,
		i_death = 65783,
		i_rebalance_hp = 65784,
		i_target_cancel = 65786,
		i_target_me = 65787,
		i_teleport = 65788,
		i_install_camp_ex = 65789,
		i_m_attack_mp = 65790,
		i_npc_kill = 65791,
		i_betray = 65792,
		i_call_pc = 65793,
		i_change_skill_level = 65794,
		i_skill_turning = 65796,
		i_call_party = 65797,
		i_m_attack_range = 65798,
		i_p_attack_by_dist = 65799,
		i_pledge_send_system_message = 65801,
		i_real_damage = 65802,
		i_capture_flag_start = 65804,
		i_capture_flag = 65805,
		i_convert_item = 65806,
		i_detect_object = 65807,
		i_mount_for_event = 65808,
		i_dismount_for_event = 65809,
		i_set_skill = 65810,
		i_vp_up = 65811,
		i_get_agro = 65812,
		i_teleport_to_target = 65813,
		i_install_advance_base = 65814,
		i_uninstall_advance_base = 65815,
		i_capture_ownthing = 65816,
		i_capture_ownthing_start = 65817,
		i_collecting = 65818,
		i_my_summon_kill = 65819,
		i_despawn = 65820,
		i_event_agathion_reuse_delay = 65821,
		cub_m_attack = 65822,
		cub_hp_drain = 65823,
		cub_heal = 65824,
		cub_hp = 65825,
		cub_physical_attack = 65826,
		cub_physical_defence = 65827,
		cub_attack_speed = 65828,
		cub_block_act = 65829,
		t_hp = 65830,
		t_mp = 65831,
		t_hp_fatal = 65832,
		p_transform = 65833,
		p_transform_hangover = 65834,
		p_transfer_damage_pc = 65835,
		p_soul_eating = 65836,
		p_block_attack = 65837,
		p_disarm = 65838,
		p_defence_critical_rate = 65839,
		p_defence_critical_damage = 65840,
		p_resist_dd_magic = 65841,
		p_physical_attack = 65842,
		p_physical_defence = 65843,
		p_hp_regen = 65844,
		p_mp_regen = 65845,
		p_mp_regen_add = 65846,
		p_max_mp_add = 65847,
		p_magical_attack_add = 65849,
		p_heal_effect_add = 65850,
		p_speed = 65851,
		p_create_item = 65852,
		p_create_common_item = 65853,
		p_attack_speed = 65854,
		p_magic_speed = 65855,
		p_remove_equip_penalty = 65856,
		p_crystallize = 65857,
		p_avoid = 65858,
		p_luck = 65859,
		p_magical_defence = 65860,
		p_attack_attribute = 65863,
		p_defence_attribute = 65864,
		p_attack_trait = 65865,
		p_defence_trait = 65866,
		p_block_move = 65867,
		p_block_act = 65868,
		p_block_controll = 65869,
		p_block_spell = 65870,
		p_block_getdamage = 65871,
		p_fear = 65872,
		p_max_hp = 65873,
		p_max_mp = 65874,
		p_max_cp = 65875,
		p_hit = 65876,
		p_magical_attack = 65877,
		p_attack_range = 65878,
		p_critical_rate = 65879,
		p_critical_damage = 65880,
		p_reuse_delay = 65881,
		p_reduce_cancel = 65882,
		p_attack_speed_by_weapon = 65883,
		p_magic_speed_by_weapon = 65884,
		p_shield_defence_rate = 65885,
		p_hp_regen_by_move_mode = 65886,
		p_mp_regen_by_move_mode = 65887,
		p_avoid_by_move_mode = 65888,
		p_safe_fall_height = 65889,
		p_breath = 65890,
		p_damage_shield = 65891,
		p_passive = 65892,
		p_avoid_agro = 65893,
		p_weight_limit = 65894,
		p_set_collected = 65896,
		p_set_cloak_slot = 65897,
		p_cubic_mastery = 65898,
		p_weight_penalty = 65899,
		p_mana_charge = 65900,
		p_transfer_damage_summon = 65901,
		p_heal_effect = 65902,
		p_area_damage = 65903,
		p_hit_at_night = 65904,
		p_2h_sword_bonus = 65905,
		p_2h_blunt_bonus = 65906,
		p_vampiric_attack = 65907,
		p_critical_rate_by_hp1 = 65908,
		p_critical_rate_by_hp2 = 65909,
		p_physical_attack_by_hp1 = 65910,
		p_physical_attack_by_hp2 = 65911,
		p_physical_defence_by_hp1 = 65912,
		p_avoid_rate_by_hp1 = 65914,
		p_avoid_rate_by_hp2 = 65915,
		p_attack_speed_by_hp2 = 65917,
		p_fatal_blow_rate = 65918,
		p_critical_rate_position_bonus = 65919,
		p_reduce_drop_penalty = 65920,
		p_physical_shield_defence = 65921,
		p_physical_armor_hit = 65922,
		p_physical_polarm_target_single = 65923,
		p_magic_critical_rate = 65924,
		p_magic_mp_cost = 65925,
		p_physical_shield_defence_angle_all = 65926,
		p_pvp_physical_attack_dmg_bonus = 65927,
		p_pvp_physical_skill_dmg_bonus = 65928,
		p_pvp_magical_skill_dmg_bonus = 65929,
		p_pvp_magical_skill_defence_bonus = 65930,
		p_pvp_physical_attack_defence_bonus = 65931,
		p_pvp_physical_skill_defence_bonus = 65932,
		p_fishing_mastery = 65933,
		p_abnormal_rate_limit = 65934,
		p_block_skill_physical = 65937,
		p_block_skill_special = 65938,
		p_block_buff = 65939,
		p_block_debuff = 65940,
		p_block_buff_slot = 65941,
		p_reflect_skill = 65942,
		p_skill_critical = 65943,
		p_skill_critical_probability = 65944,
		p_critical_damage_position = 65945,
		p_resist_dispel_by_category = 65946,
		p_resist_abnormal_by_category = 65947,
		p_preserve_abnormal = 65948,
		p_enlarge_storage = 65949,
		p_enlarge_abnormal_slot = 65950,
		p_hit_number = 65951,
		p_cp_regen = 65952,
		p_betray = 65954,
		p_trigger_skill_by_dmg = 65955,
		p_trigger_skill_by_attack = 65956,
		p_trigger_skill_by_skill = 65957,
		p_trigger_skill_by_avoid = 65958,
		p_channel_clan = 65959,
		p_change_fishing_mastery = 65960,
		p_resurrection_special = 65961,
		p_avoid_skill = 65962,
		p_counter_skill = 65963,
		p_pk_protect = 65964,
		p_expand_deco_slot = 65965,
		p_target_me = 65966,
		p_limit_hp = 65967,
		p_limit_mp = 65968,
		p_limit_cp = 65969,
		p_skill_power = 65971,
		p_magic_defence_critical_dmg = 65973,
		p_magic_critical_dmg = 65974,
		p_recovery_vp = 65977,
		p_hide = 65978,
		p_hate_attack = 65979,
		p_reflect_dd = 65980,
		p_mp_vampiric_attack = 65981,
		p_block_resurrection = 65982,
		p_block_chat = 65983,
		p_block_party = 65984,
		p_violet_boy = 65985,
		p_dominion_transform = 65986,
		p_stat_up = 65987,
		p_cheapshot = 65988,
		p_exp_modify = 65989,
		p_sp_modify = 65990,
		p_crystal_grade_modify = 65991,
		c_mp = 65992,
		c_rest = 65993,
		c_chameleon_rest = 65994,
		c_mp_by_level = 65995,
		c_fake_death = 65996,
		c_hp = 65997,
		all = 65998,
		STRING = 65999,
		CONSTANT = 66000,
		INT = 66001,
		FLOAT = 66002,
		diff = 66003,
		per = 66003,
		front = 66004,
		back = 66004,
		side = 66004,
		attr_none = 66005,
		attr_unholy = 66005,
		attr_fire = 66005,
		attr_water = 66005,
		attr_wind = 66005,
		attr_earth = 66005,
		attr_holy = 66005,
		trait_none = 66006,
		trait_shock = 66006,
		trait_bow = 66006,
		trait_crossbow = 66006,
		trait_poison = 66006,
		trait_sleep = 66006,
		trait_hold = 66006,
		trait_derangement = 66006,
		trait_bleed = 66006,
		trait_bug_weakness = 66006,
		trait_beast_weakness = 66006,
		trait_animal_weakness = 66006,
		trait_dragon_weakness = 66006,
		trait_plant_weakness = 66006,
		trait_paralyze = 66006,
		trait_boss = 66006,
		trait_pole = 66006,
		trait_death = 66006,
		trait_construct_weakness = 66006,
		trait_giant_weakness = 66006,
		trait_sword = 66006,
		trait_blunt = 66006,
		trait_dagger = 66006,
		trait_dual = 66006,
		trait_dualfist = 66006,
		trait_ancientsword = 66006,
		trait_rapier = 66006,
		trait_dualdagger = 66006,
		trait_physical_blockade = 66006,
		trait_etc = 66006,
		trait_valakas = 66006,
		trait_gust = 66006,
		trait_turn_stone = 66006,
		trait_fist = 66006,
		trait_root_physically = 66006,
		sword = 66007,
		blunt = 66007,
		dagger = 66007,
		bow = 66007,
		dualdagger = 66007,
		pole = 66007,
		dualfist = 66007,
		fist = 66007,
		dual = 66007,
		rapier = 66007,
		ancientsword = 66007,
		crossbow = 66007,
		weapon_etc = 66007,
		armor_none = 66008,
		armor_light = 66008,
		armor_heavy = 66008,
		armor_magic = 66008,
		armor_sigil = 66008,
		enemy = 66009,
		self = 66009,
		enemy_only = 66009,
		holything = 66009,
		target = 66009,
		summon = 66009,
		door_treasure = 66009,
		pc_body = 66009,
		npc_body = 66009,
		others = 66009,
		ground = 66009,
		my_party = 66009,
		advance_base = 66009,
		item = 66009,
		fortress_flagpole = 66009,
		wyvern_target = 66009,
		artillery = 66009,
		race_undead = 66011,
		race_divine = 66011,
		race_kamael = 66011,
		race_construct = 66011,
		race_humanoid = 66011,
		single = 66012,
		party = 66012,
		range = 66012,
		fan = 66012,
		party_pledge = 66012,
		point_blank = 66012,
		dead_pledge = 66012,
		pledge = 66012,
		square = 66012,
		square_pb = 66012,
		static_object_scope = 66012,
		wyvern_scope = 66012,
		balakas_scope = 66012,
		friend_ = 66013,
		not_friend = 66013,
		undead_real_enemy = 66013,
		object_dead_npc_body = 66013,
		invisible = 66013,
		hidden_place = 66013,
		wyvern_object = 66013,
		clan = 66013,
		inventory_normal = 66014,
		trade_sell = 66014,
		trade_buy = 66014,
		recipe_dwarven = 66014,
		recipe_common = 66014,
		storage_private = 66014,
		inventory_waist = 66014,
		enemy_all = 66015,
		boss = 66015,
		pk = 66015,
		mob = 66015,
		ia_fire = 66016,
		ia_water = 66016,
		ia_wind = 66016,
		ia_earth = 66016,
		ia_holy = 66016,
		ia_unholy = 66016,
		// additional:
		olympiad_use = 66017,
		op_skill_acquire = 66018
	};
};
