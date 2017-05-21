
#include <Server/CSkillOperateCondition_op_check_abnormal.h>
#include <Server/CSkillInfo.h>
#include <Common/Utils.h>

CSkillOperateCondition_op_check_abnormal *CSkillOperateCondition_op_check_abnormal::last = 0;

void CSkillOperateCondition_op_check_abnormal::Init()
{
	WriteInstructionCall(0x9B5C72, FnPtr(Alloc));
	WriteMemoryQWORD(0xD060C0, FnPtr(&CSkillOperateCondition_op_check_abnormal::CanUse_));
}

CSkillOperateCondition_op_check_abnormal* CSkillOperateCondition_op_check_abnormal::Alloc(const size_t size)
{
	last = reinterpret_cast<CSkillOperateCondition_op_check_abnormal*(*)(const size_t)>(0x9DAE50)(
		sizeof(CSkillOperateCondition_op_check_abnormal));
	if (last) {
		last->invert = false;
	}
	return last;
}

bool CSkillOperateCondition_op_check_abnormal::CanUse_(CCreature *caster, const CSkillInfo *skillInfo, class CObject *target)
{
	return reinterpret_cast<
		bool(*)(CSkillOperateCondition_op_check_abnormal*, const class CCreature*,
			const CSkillInfo*, class CObject*)>(0x82E7E4)(
				this, caster, skillInfo, target) ^ invert;
}

CompileTimeOffsetCheck(CSkillOperateCondition_op_check_abnormal, invert, 0x10);

