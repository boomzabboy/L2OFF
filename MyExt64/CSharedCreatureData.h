
#pragma once

#include <windows.h>

class CSharedCreatureData {
public:
	/* 0x0000 */ unsigned char padding0x0000[0x28];
	/* 0x0028 */ UINT32 index;
	/* 0x002C */ unsigned char padding0x002C[0x78];
	/* 0x00A4 */ WCHAR name[25];
	/* 0x00D6 */ unsigned char padding0x00D6[0x5D6];
	/* 0x06AC */ INT32 storeMode;
	/* 0x06B0 */ unsigned char padding0x06B0[0xF4];
	/* 0x07A4 */ UINT32 level;
	/* 0x07A8 */ unsigned char padding0x07A8[0x120];
	/* 0x08C8 */ UINT32 builder;
	/* 0x08CC */ unsigned char padding0x08CC[0x1B0];
	/* 0x0A7C */ UINT32 npcClassId;
	/* 0x0A80 */ unsigned char padding0x0A80[0x378];
	/* 0x0DF8 */
};

