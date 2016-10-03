
#pragma once

#include <windows.h>

template<size_t size>
class CIOBuffer {
public:
	/* 0x0000 */ unsigned char padding0[0x0010];
	/* 0x0010 */ unsigned char buffer[size];
	/* size + 0x0010 */ unsigned char padding1[0x0024];
	/* size + 0x0034 */ UINT32 threadIndex;
};

