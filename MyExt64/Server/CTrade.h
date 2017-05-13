
#pragma once

#include <windows.h>

class CTrade {
public:
	static void Init();

	static void PressDoneHelper(void *rsp, int type, const wchar_t *format, ...);

	unsigned char padding0x0[0x28];
	UINT32 starterId;
	UINT32 targetId;
};

