
#pragma once

#include <windows.h>
#include <Server/CSkillInfo.h>

class CSkillAction2 {
public:
	static void Init();

	/* 0x0000 */ unsigned char padding0x0000[0x0008-0x0000];
	/* 0x0008 */ UINT32 casterId;
	/* 0x000C */ unsigned char padding0x000C[0x0010-0x000C];
	/* 0x0010 */ UINT32 targetId;
	/* 0x0014 */ unsigned char padding0x0014[0x0068-0x0014];
	/* 0x0068 */ CSkillInfo *skillInfo;
};

