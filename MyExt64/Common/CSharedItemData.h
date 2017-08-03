
#pragma once

#include <Common/Utils.h>

class CSharedItemData {
public:
	static void InitServer();
	static void InitNpc();

	class Ext {
	public:
		// NO CONSTRUCTOR/DESTRUCTOR - USE ONLY PLAIN OLD DATA! EVERYTHING IS 0 BY DEFAULT!
		bool isPrivateStore;
		bool isPrivateStoreSet;
		bool isOlympiadCanUse;
	};

	/* 0x0000 */ unsigned char padding0x0000[0x0008 - 0x0000];
	/* 0x0008 */ UINT32 someType;
	/* 0x000C */ unsigned char padding0x000C[0x0020 - 0x000C];
	/* 0x0020 */ class CSkillInfo *itemSkill;
	/* 0x0028 */ unsigned char padding0x0028[0x0108 - 0x0028];
	/* 0x0108 */ UINT32 dropPeriod;
	/* 0x010C */ unsigned char padding0x010C[0x0148 - 0x010C];
	/* 0x0148 */ Ext ext;
};

