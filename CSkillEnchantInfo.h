
#pragma once

#include <windows.h>

class CSkillEnchantInfo {
public:
	/* 0x0000 */ UINT32 skillId;
	/* 0x0004 */ UINT32 newEnchantLevel;
	/* 0x0008 */ UINT32 requiredSkillLevel;
	/* 0x000C */ UINT32 oldEnchantLevel;
	/* 0x0010 */ unsigned char paddinx0x0010[0x18];
	/* 0x0028 */ UINT32 requiredItems[4];
	/* 0x0038 */ UINT64 requiredItemCounts[4];
};

