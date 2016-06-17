
#pragma once

#include <windows.h>

class CSharedCreatureData {
public:
	/* 0x0000 */ unsigned char padding0x0000[0xa4];
	/* 0x00A4 */ WCHAR name[25];
	/* 0x00D6 */ unsigned char padding0x00D6[0x6ce];
	/* 0x07A4 */ UINT32 level;
};

