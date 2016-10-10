
#pragma once

#include <Server/CObject.h>
#include <Server/CContributeData.h>
#include <Server/CSkillInfo.h>
#include <windows.h>
#include <vector>

class CItem : CObject {
public:
	class WorldInfo {
	public:
		/* 0x0000 */ void *unknown;
		/* 0x0008 */ double x;
		/* 0x0010 */ double y;
		/* 0x0018 */ double z;
		/* 0x0020 */ unsigned char padding0x0020[0x0050 - 0x0020];
		/* 0x0050 */ bool pickable;
		/* 0x0051 */ unsigned char padding0x0051[0x0068 - 0x0051];
		/* 0x0068 */ UINT64 count;
	};

	class CContributeData* GetContributeData();

	/* 0x0000 */ unsigned char padding0x0000[0x001C - 0x0000];
	/* 0x001C */ UINT32 itemId;
	/* 0x0020 */ unsigned char padding0x0020[0x0048 - 0x0020];
	/* 0x0048 */ WorldInfo *worldInfo;
	/* 0x0050 */ unsigned char padding0x0050[0x0078 - 0x0050];
	/* 0x0078 */ std::vector<CSkillInfo*> skills;
	/* 0x0098 */ unsigned char padding0x0098[0x00B8 - 0x0098];
	/* 0x00B8 */ UINT32 contributeDataObjectId;
};

