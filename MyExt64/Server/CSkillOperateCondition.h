
#pragma once

#include <windows.h>

class CSkillOperateCondition {
public:
	virtual bool CanUse(class CCreature *caster, const class CSkillInfo *skillInfo, class CObject *target) = 0;
};

