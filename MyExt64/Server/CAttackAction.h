
#pragma once

class CAttackAction {
public:
	static void Init();

	static bool __cdecl CheckAttackValidity(class CCreature *attacker, class CCreature *target);
};

