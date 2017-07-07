
#include <Server/CAttackAction.h>
#include <Server/CCreature.h>
#include <Server/CSummon.h>
#include <Server/CUser.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>
#include <Common/Config.h>

void CAttackAction::Init()
{
	WriteInstructionCall(0x703C3F, reinterpret_cast<UINT32>(CheckAttackValidity));

	WriteInstructionCall(0x534ED4 + 0x112, FnPtr(GenerateAttackTargetData));
	WriteInstructionCall(0x700234 + 0x242, FnPtr(GenerateAttackTargetData));
	WriteInstructionCall(0x7039A8 + 0xB93, FnPtr(GenerateAttackTargetData));
	WriteInstructionCall(0x7039A8 + 0xD07, FnPtr(GenerateAttackTargetData));
	WriteInstructionCall(0x7039A8 + 0xD3C, FnPtr(GenerateAttackTargetData));
	WriteInstructionCall(0x7039A8 + 0xD64, FnPtr(GenerateAttackTargetData));
}

bool CAttackAction::CheckAttackValidity(CCreature *attacker, CCreature *target)
{
	GUARDED;

	if (target && target->IsBoss() && target->sd->npcClassId == 1029028) { // valakas
		if (abs(attacker->sd->z - target->sd->z) > 128) {
			return false;
		}
	}
	return reinterpret_cast<bool(*)(CCreature*, CCreature*)>(0x6FC288)(attacker, target);
}

void CAttackAction::GenerateAttackTargetData(CCreature *attacker, CObject *target, CAttackTargetData *data, bool *b, double d)
{
	reinterpret_cast<void(*)(CCreature*, CObject*, CAttackTargetData*, bool*, double)>(0x6FF14C)(
		attacker, target, data, b, d);

	if (!attacker || !target || !data->isHit) return;
	if (data->damage <= 1.0) return;

	double reduction = Config::Instance()->server->epilogueDamageReduction78Plus;
	if (reduction <= 0.0) return;

	if (!attacker->IsUserOrSummon()) return;
	CCreature *targetCreature = reinterpret_cast<CCreature*>(target);
	if (!targetCreature->IsValidCreature()) return;
	if (targetCreature->IsUserOrSummon()) return;
	int targetLevel = targetCreature->GetLevel();
	if (targetLevel <= 78) return;
	int attackerLevel = attacker->GetLevel();
	if (attacker->IsSummon()) {
		CUser *master = reinterpret_cast<CSummon*>(attacker)->GetUserOrMaster();
		if (master) {
			attackerLevel = master->GetLevel();
		}
	}
	if (targetLevel - attackerLevel > 1) {
		double rate = 1.0 - reduction;
		if (rate < 0) rate = 0;
		data->damage *= rate;
	}
}

