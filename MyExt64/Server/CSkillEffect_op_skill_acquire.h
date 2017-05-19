
#pragma once

#include <Server/CSkillOperateCondition.h>

class CSkillEffect_op_skill_acquire : public CSkillOperateCondition {
public:
	CSkillEffect_op_skill_acquire(UINT32 skillId, bool learned);

	virtual bool CanUse(class CCreature *caster, const class CSkillInfo *skillInfo, class CObject *target);

	UINT32 skillId;
	bool learned;
};

