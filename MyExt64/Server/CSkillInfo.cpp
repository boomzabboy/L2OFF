
#include <Server/CSkillInfo.h>
#include <Server/CCreature.h>
#include <Server/CUser.h>
#include <Server/CSummon.h>
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

	WriteInstructionCall(0x554168 + 0x154, FnPtr(&CSkillInfo::CanUsedBy));
	WriteInstructionCall(0x554168 + 0x49E, FnPtr(&CSkillInfo::CanUsedBy));
	WriteInstructionCall(0x716FE8 + 0x1A4, FnPtr(&CSkillInfo::CanUsedBy));
	WriteInstructionCall(0x81EE98 + 0x82, FnPtr(&CSkillInfo::CanUsedBy));
	WriteInstructionCall(0x8FD128 + 0xE2, FnPtr(&CSkillInfo::CanUsedBy));

	WriteInstructionCallJmpEax(0x81D243, FnPtr(IsValidTargetHelper));
	WriteMemoryDWORD(0x820B65 + 6, end);
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
	if (targetType == enemy_not && attacker && target && target->IsEnemyTo(attacker)) {
		return false;
	}
	return reinterpret_cast<bool(*)(void*, CCreature*, CCreature*, bool)>(0x81CF38)(this, attacker, target, b);
}

UINT64 CSkillInfo::IsValidTargetHelper(UINT32 targetType)
{
	if (targetType == enemy_not) {
		return 0x81D578;
	} else if (targetType > door_treasure) {
		return 0x81D697;
	} else {
		return 0x81D24C;
	}
}

void CSkillInfo::ActivateSkill(CCreature *caster, CObject *target, double unknown1, void *unknown2, int unknown3, double unknown4)
{
	reinterpret_cast<void(*)(CSkillInfo*, CCreature*, CObject*, double, void*, int, double)>(0x81F3F0)(
		this, caster, target, unknown1, unknown2, unknown3, unknown4);
}

bool CSkillInfo::PushCondition(class CSkillOperateCondition *condition, const int operateConditionTarget)
{
	return reinterpret_cast<bool(*)(CSkillInfo*, class CSkillOperateCondition*, const int)>(0x822248)(this, condition, operateConditionTarget);
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

bool CSkillInfo::CanUsedBy(CCreature *caster, bool b) const
{
	bool ret = reinterpret_cast<bool(*)(const CSkillInfo*, CCreature*, bool)>(0x81BFA0)(this, caster, b);
	if (!ret || !caster || ext.olympiadUse) {
		return ret;
	}
	if (caster->IsUser()) {
		if (reinterpret_cast<CUser*>(caster)->IsInOlympiad()) {
			return false;
		}
	} else if (caster->IsSummon()) {
		CUser *master = reinterpret_cast<CSummon*>(caster)->GetUserOrMaster();
		if (master && master->IsInOlympiad()) {
			return false;
		}
	}
	return true;
}

CSkillInfo::Ext::Ext() : olympiadUse(true)
{
}

CSkillInfo::Ext::~Ext()
{
}

CompileTimeOffsetCheck(CSkillInfo, effects, 0x218);
CompileTimeOffsetCheck(CSkillInfo, ext, 0x398);
