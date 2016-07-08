
#include "CSkillInfo.h"
#include "CCreature.h"
#include "CSharedCreatureData.h"
#include "Utils.h"

void CSkillInfo::Init()
{
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
	if (target && target->IsBoss() && target->sd->npcClassId == 1029028) { // valakas
		return attacker->sd->z >= -1500; // too high?
	}
	return reinterpret_cast<bool(*)(void*, CCreature*, CCreature*, bool)>(0x81CF38)(this, attacker, target, b);
}

