
#pragma once

#include <windows.h>

class L2SkillFunc {
public:
	static void Init();

	static double CalculateDamage(class CCreature *attacker, class CObject *target,
	                              const class CSkillInfo *skillInfo, const double d,
	                              const int i, const int j, const bool b);

	static bool CheckResistedWrapper(class CCreature *attacker, class CCreature *target, UINT64 x,
	                                 double d1, int i1, double d2, bool b1, double d3, double d4);
};
