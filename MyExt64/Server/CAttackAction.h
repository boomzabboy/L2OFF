
#pragma once

#include <windows.h>

class CAttackAction {
public:
	class CAttackTargetData {
	public:
		double damage;
		bool isHit;
	};

	static void Init();

	static bool __cdecl CheckAttackValidity(class CCreature *attacker, class CCreature *target);
	static void GenerateAttackTargetData(class CCreature *attacker, class CObject *target, CAttackTargetData *data, bool *b, double d);

	/* 0x0000 */ unsigned char padding0x0000[0x0008-0x0000];
	/* 0x0008 */ UINT32 attackerId;
	/* 0x000C */ unsigned char padding0x000C[0x0010-0x000C];
	/* 0x0010 */ UINT32 targetId;
	/* 0x0014 */ unsigned char padding0x0014[0x0018-0x0014];
};

