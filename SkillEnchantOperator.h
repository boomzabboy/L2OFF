
#pragma once

#include <windows.h>

class SkillEnchantOperator {
public:
	static SkillEnchantOperator* __cdecl GetOperator(UINT32 type);
	int CalculateProb(class CSkillEnchantInfo *info, int level);

	/* 0x0000 */ void *vtable;
	/* 0x0008 */ UINT32 requirementModifier;
	/* 0x000C */ unsigned char padding[0x14];
	/* 0x0020 */ UINT32 operatorType;
};

