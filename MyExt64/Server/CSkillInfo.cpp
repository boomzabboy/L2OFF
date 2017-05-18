
#include <Server/CSkillInfo.h>
#include <Server/CCreature.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>

void CSkillInfo::Init()
{
	WriteMemoryDWORD(0x9A808F, sizeof(CSkillInfo));
	WriteMemoryDWORD(0x9B3A11, sizeof(CSkillInfo));
	WriteInstructionCall(0x9A80A5, FnPtr(&CSkillInfo::Constructor));
	WriteInstructionCall(0x9B3A2C, FnPtr(&CSkillInfo::Constructor));
	WriteMemoryQWORD(0xBFEDD8, FnPtr(&CSkillInfo::Destructor));

	WriteInstructionCall(0x548254 + 0x26C, reinterpret_cast<UINT32>(IsValidTargetWrapper));
	WriteInstructionCall(0x572CC4 + 0xA9, reinterpret_cast<UINT32>(IsValidTargetWrapper));
	WriteInstructionCall(0x573734 + 0xD3, reinterpret_cast<UINT32>(IsValidTargetWrapper));
	WriteInstructionCall(0x7123F0 + 0x464, reinterpret_cast<UINT32>(IsValidTargetWrapper));
}

bool __cdecl CSkillInfo::IsValidTargetWrapper(CSkillInfo *self, CCreature *attacker, CCreature *target, bool b)
{
	return self->IsValidTarget(attacker, target, b);
}

bool CSkillInfo::IsValidTarget(CCreature *attacker, CCreature *target, bool b)
{
	GUARDED;

	if (target && target->IsBoss() && target->sd->npcClassId == 1029028) { // valakas
		if (abs(attacker->sd->z - target->sd->z) > 128) {
			return false;
		}
	}
	return reinterpret_cast<bool(*)(void*, CCreature*, CCreature*, bool)>(0x81CF38)(this, attacker, target, b);
}

void CSkillInfo::ActivateSkill(CCreature *caster, CObject *target, double unknown1, void *unknown2, int unknown3, double unknown4)
{
	reinterpret_cast<void(*)(CSkillInfo*, CCreature*, CObject*, double, void*, int, double)>(0x81F3F0)(
		this, caster, target, unknown1, unknown2, unknown3, unknown4);
}

CSkillInfo* CSkillInfo::Constructor()
{
	CSkillInfo *ret = reinterpret_cast<CSkillInfo*(*)(CSkillInfo*)>(0x82093C)(this);
	new (&ret->ext) Ext();
	return ret;
}

void CSkillInfo::Destructor(bool isMemoryFreeUsed)
{
	ext.~Ext();
	reinterpret_cast<void(*)(CSkillInfo*)>(0x81E994)(this);
}

CSkillInfo::Ext::Ext() : olympiadUse(false)
{
}

CSkillInfo::Ext::~Ext()
{
}

CompileTimeOffsetCheck(CSkillInfo, effects, 0x218);
CompileTimeOffsetCheck(CSkillInfo, ext, 0x396);
