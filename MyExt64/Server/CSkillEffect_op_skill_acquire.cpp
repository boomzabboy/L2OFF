
#include <Server/CSkillEffect_op_skill_acquire.h>
#include <Server/CCreature.h>

CSkillEffect_op_skill_acquire::CSkillEffect_op_skill_acquire(UINT32 skillId, bool learned) : skillId(skillId), learned(learned)
{
}

bool CSkillEffect_op_skill_acquire::CanUse(CCreature *caster, const class CSkillInfo *skillInfo, class CObject *target)
{
	(void) skillInfo;
	(void) target;

	return learned == (caster && caster->GetAcquiredSkillLevel(skillId) > 0);
}

