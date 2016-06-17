
#pragma once

#include <windows.h>
#include "CSharedCreatureData.h"

class CUser {
public:
	int GetAcquiredSkillLevel(int skillId);
	int GetLevel();
	wchar_t* GetName();

	/* 0x0000 */ unsigned char padding0x0000[0xa90];
	/* 0x0a90 */ CSharedCreatureData *sd;
};

