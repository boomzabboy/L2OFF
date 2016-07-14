
#include <Server/CAttackAction.h>
#include <Server/CCreature.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>

void CAttackAction::Init()
{
	WriteInstructionCall(0x703C3F, reinterpret_cast<UINT32>(CheckAttackValidity));
}

bool CAttackAction::CheckAttackValidity(CCreature *attacker, CCreature *target)
{ GUARDED

	if (target && target->IsBoss() && target->sd->npcClassId == 1029028) { // valakas
		return attacker->sd->z >= -1500; // too high?
	}
	return reinterpret_cast<bool(*)(CCreature*, CCreature*)>(0x6FC288)(attacker, target);
}

