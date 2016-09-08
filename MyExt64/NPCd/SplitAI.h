
#pragma once

#include <windows.h>

class SplitAI {
public:
	static void Init();

	static void* ReadSplitAI(const wchar_t *filename, UINT32 *filesize);

	static unsigned char *buffer;
};

