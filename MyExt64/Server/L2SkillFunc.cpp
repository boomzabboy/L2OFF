
#include <Server/L2SkillFunc.h>
#include <Server/CCreature.h>
#include <Server/CSummon.h>
#include <Server/CUser.h>
#include <Server/CSkillInfo.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>
#include <Common/Config.h>

void L2SkillFunc::Init()
{
	WriteInstructionCall(0x845D6C + 0xBD, FnPtr(CalculateDamage));
	WriteInstructionCall(0x845EE4 + 0xDD, FnPtr(CalculateDamage));
	WriteInstructionCall(0x8492B4 + 0xC3, FnPtr(CalculateDamage));

	static const char *CheckResistedHelper =
		/* 0x0000 */ "\x49\xC1\xE0\x20"     // shl r8, 0x20
		/* 0x0004 */ "\x41\x88\xD0"         // mov r8b, dl
		/* 0x0007 */ "\x4C\x89\xE1"         // mov rcx, r12
		/* 0x000A */ "\x4C\x89\xEA"         // mov rdx, r13
		/* 0x000D */ "\xE9\x00\x00\x00\x00" // jmp ...
		/* 0x0012 */ ;
	WriteInstructionJmp(reinterpret_cast<UINT32>(CheckResistedHelper) + 0xD, FnPtr(CheckResistedWrapper));
	WriteInstructionCall(0x849E53, reinterpret_cast<UINT32>(CheckResistedHelper));
	MakeExecutable(reinterpret_cast<UINT32>(CheckResistedHelper), 0x12);
}

double L2SkillFunc::CalculateDamage(CCreature *attacker, CObject *target, const CSkillInfo *skillInfo,
                                    const double d, const int i, const int j, const bool b)
{
	double ret = reinterpret_cast<double(*)(CCreature*, CObject*, const CSkillInfo*, const double, const int, const int, const bool)>(
		0x845648)(attacker, target, skillInfo, d, i, j, b);

	if (!attacker || !target) return ret;
	if (ret <= 1.0) return ret;

	double reduction = Config::Instance()->server->epilogueDamageReduction78Plus;
	if (reduction <= 0.0) return ret;

	if (!attacker->IsUserOrSummon()) return ret;
	CCreature *targetCreature = reinterpret_cast<CCreature*>(target);
	if (!targetCreature->IsValidCreature()) return ret;
	if (targetCreature->IsUserOrSummon()) return ret;
	int targetLevel = targetCreature->GetLevel();
	if (targetLevel <= 78) return ret;
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
		return ret * rate;
	}
	return ret;
}

bool L2SkillFunc::CheckResistedWrapper(class CCreature *attacker, class CCreature *target, UINT64 x,
                                       double d1, int i1, double d2, bool b1, double d3, double d4)
{
	do {
		if (!attacker || !target) break;

		double reduction = Config::Instance()->server->epilogueMagicChanceReduction78Plus;
		if (reduction <= 0.0) break;

		if (!attacker->IsUserOrSummon()) break;
		CCreature *targetCreature = reinterpret_cast<CCreature*>(target);
		if (!targetCreature->IsValidCreature()) break;
		if (targetCreature->IsUserOrSummon()) break;
		int targetLevel = targetCreature->GetLevel();
		if (targetLevel <= 78) break;
		int attackerLevel = attacker->GetLevel();
		if (attacker->IsSummon()) {
			CUser *master = reinterpret_cast<CSummon*>(attacker)->GetUserOrMaster();
			if (master) {
				attackerLevel = master->GetLevel();
			}
		}
		if (targetLevel - attackerLevel > 2) {
			double r = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX));
			if (reduction > r) {
				return true;
			}
		}
	} while (0);

	return reinterpret_cast<bool(*)(bool, bool, int, double, int, double, bool, double, double)>(0x849ABC)(
		1, x & 1, static_cast<int>(x >> 32), d1, i1, d2, b1, d3, d4);
}

