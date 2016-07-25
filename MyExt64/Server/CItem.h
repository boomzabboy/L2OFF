
#pragma once

#include <Server/CObject.h>
#include <Server/CContributeData.h>
#include <windows.h>

class CItem : CObject {
public:
	class CContributeData* GetContributeData();

	/* 0x0000 */ unsigned char padding0x0000[0x001C - 0x0000];
	/* 0x001C */ UINT32 itemId;
	/* 0x0020 */ unsigned char padding0x0020[0x00B8 - 0x0020];
	/* 0x00B8 */ UINT32 contributeDataObjectId;
};

