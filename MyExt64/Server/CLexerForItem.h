
#pragma once

#include <Common/Yacc/yywclex.h>
#include <map>
#include <vector>

class CLexerForItem : public yl::yywflexer {
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
		NONE = 0,
		SEMICOLON = 59,
		ASSIGN = 61,
		LBRACKET = 123,
		RBRACKET = 125,
		item_begin = 65537,
		item_end = 65538,
		STRING = 65539,
		CONSTANT = 65540,
		PROPERTY = 65541,
		WEAPONTYPE = 65542,
		weapon = 65542,
		etcitem = 65542,
		armor = 65542,
		INT = 65544,
		action_equip = 65544,
		FLOAT = 65545,
		category = 65546,
		default_action = 65547,
		recipe_id = 65548,
		item_equip_option = 65549,
		is_premium = 65550,
		capsuled_items = 65551,
		use_condition = 65576,
		equip_condition = 65586,
		ec_race = 65588,
		default_price = 65610,
		immediate_effect = 65611,
		ex_immediate_effect = 65612,
		item_multi_skill_list = 65613,
		unequip_skill = 65614,
		base_attribute_defend = 65615,
		duration = 65616,
		use_skill_distime = 65617,
		period = 65618,
		item_skill = 65619,
		critical_attack_skill = 65620,
		attack_skill = 65621,
		magic_skill = 65622,
		keep_type = 65624,
		can_move = 65625,
		is_trade = 65626,
		is_drop = 65627,
		is_destruct = 65628,
		crystal_type = 65629,
		// additional:
		is_private_store = 65630,
		is_olympiad_can_use = 65631
	};
};

