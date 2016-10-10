
#pragma once

#include <windows.h>

class CSkillInfo {
public:
	static void Init();

	static bool __cdecl IsValidTargetWrapper(CSkillInfo *self, class CCreature *attacker, class CCreature *target, bool b);

	bool IsValidTarget(class CCreature *attacker, class CCreature *target, bool b);
	void ActivateSkill(class CCreature *caster, class CObject *target, double unknown1, void *unknown2, int unknown3, double unknown4);

	/* 0x0000 */ unsigned char padding0x0000[0x0010 - 0x0000];
	/* 0x0010 */ UINT32 skillId;
	/* 0x0014 */ UINT32 level;
};

