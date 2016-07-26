
#pragma once

#include <Server/CObject.h>
#include <Server/CContributeData.h>
#include <windows.h>

class CItem : CObject {
public:
	class WorldInfo {
	public:
		/* 0x0000 */ void *unknown;
		/* 0x0008 */ double x;
		/* 0x0010 */ double y;
		/* 0x0018 */ double z;
		/* 0x0020 */ unsigned char padding0x0020[0x0030];
		/* 0x0050 */ bool pickable;
	};

	class CContributeData* GetContributeData();

	/* 0x0000 */ unsigned char padding0x0000[0x001C - 0x0000];
	/* 0x001C */ UINT32 itemId;
	/* 0x0020 */ unsigned char padding0x0020[0x0048 - 0x0020];
	/* 0x0048 */ WorldInfo *worldInfo;
	/* 0x0050 */ unsigned char padding0x0050[0x00B8 - 0x0050];
	/* 0x00B8 */ UINT32 contributeDataObjectId;
};

