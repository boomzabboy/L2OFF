
#pragma once

#include <windows.h>

class CSkillEnchantInfo {
public:
	/* 0x0000 */ UINT32 skillId;
	/* 0x0004 */ unsigned char padding0x0004[0x10];
	/* 0x0014 */ UINT32 newEnchantLevel;
	/* 0x0018 */ UINT32 oldEnchantLevel;
	/* 0x001C */ unsigned char padding0x000C[0xc];
	/* 0x0028 */ UINT32 requiredItems[4];
	/* 0x0048 */ UINT32 *requiredItemCounts[4];
};

