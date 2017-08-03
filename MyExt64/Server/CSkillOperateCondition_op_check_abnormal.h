
#pragma once

#include <Server/CSkillOperateCondition.h>

class CSkillOperateCondition_op_check_abnormal : public CSkillOperateCondition {
public:
	static void Init();
	static CSkillOperateCondition_op_check_abnormal* Alloc(const size_t size);

	static CSkillOperateCondition_op_check_abnormal *last;

	bool CanUse_(class CCreature *caster, const class CSkillInfo *skillInfo, class CObject *target);

	unsigned char padding0x0008[0x0010 - 0x0008];
	bool invert;
};

