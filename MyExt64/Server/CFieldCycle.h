
#pragma once

#include <windows.h>

class CFieldCycle {
public:
	static void Init();

	static void _OnStepChangedWrapper(CFieldCycle *self, int step, int time, bool b);

	/* 0x0000 */ unsigned char padding0x0000[0x0018 - 0x0000];
	/* 0x0018 */ UINT32 id;
	/* 0x001C */ unsigned char padding0x001C[0x0064 - 0x001C];
	/* 0x0064 */ UINT32 lastPointChangeTime;
};

