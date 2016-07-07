
#pragma once

#include <windows.h>

class CTrade {
public:
	unsigned char padding0x0[0x28];
	UINT32 starterId;
	UINT32 targetId;
};

