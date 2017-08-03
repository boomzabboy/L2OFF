
#include <Server/CSkillEffect_t_hp.h>
#include <Server/CCreature.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>

CSkillEffect_t_hp *CSkillEffect_t_hp::last = 0;

void CSkillEffect_t_hp::Init()
{
	WriteInstructionCall(0x9B9CB2, FnPtr(Alloc));
	WriteMemoryQWORD(0xD060F0, FnPtr(&CSkillEffect_t_hp::Tick));
}

CSkillEffect_t_hp* CSkillEffect_t_hp::Alloc(const size_t)
{
	last = reinterpret_cast<CSkillEffect_t_hp*(*)(const size_t)>(0x9DAE50)(sizeof(CSkillEffect_t_hp));
	if (last) {
		last->per = false;
	}
	return last;
}

bool CSkillEffect_t_hp::Tick(class CObject *target, double d, unsigned int i)
{
	if (target && per) {
		CCreature *creature = reinterpret_cast<CCreature*>(target);
		if (creature->IsValidCreature() && creature->sd) {
			d *= creature->sd->maxHp;
			d /= 100.0;
		}
	}
	return reinterpret_cast<bool(*)(CSkillEffect_t_hp*, class CObject*, double, unsigned int)>(0x842D2C)(
		this, target, d, i);
}

CompileTimeOffsetCheck(CSkillEffect_t_hp, per, 0x18);

