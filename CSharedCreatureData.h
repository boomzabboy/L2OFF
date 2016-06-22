
#pragma once

#include <windows.h>

class CSharedCreatureData {
public:
	/* 0x0000 */ unsigned char padding0x0000[0x28];
	/* 0x0028 */ UINT32 index;
	/* 0x002C */ unsigned char padding0x002C[0x78];
	/* 0x00A4 */ WCHAR name[25];
	/* 0x00D6 */ unsigned char padding0x00D6[0x6ce];
	/* 0x07A4 */ UINT32 level;
};

