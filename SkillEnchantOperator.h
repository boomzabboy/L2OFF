
#pragma once

#include <windows.h>

typedef class SkillEnchantOperator* (__cdecl *SkillEnchantOperatorGetOperator_t)(void*, UINT32&);

class SkillEnchantOperator {
public:
	static void Init();
	static SkillEnchantOperator* __cdecl GetOperator(UINT32 type);
	int CalculateProb(class CSkillEnchantInfo *info, int level);

protected:
	static SkillEnchantOperatorGetOperator_t OriginalGetOperator;
	static SkillEnchantOperator* __cdecl FixedGetOperator(void *self, UINT32 &type);

public:
	/* 0x0000 */ void *vtable;
	/* 0x0008 */ UINT32 requirementModifier;
	/* 0x000C */ unsigned char padding[0x14];
	/* 0x0020 */ UINT32 operatorType;
};

