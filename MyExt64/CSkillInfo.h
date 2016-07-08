
#pragma once

class CSkillInfo {
public:
	static void Init();

	static bool __cdecl IsValidTargetWrapper(CSkillInfo *self, class CCreature *attacker, class CCreature *target, bool b);

	bool IsValidTarget(class CCreature *attacker, class CCreature *target, bool b);
};

