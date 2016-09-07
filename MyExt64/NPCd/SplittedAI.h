
#pragma once

#include <windows.h>

class SplittedAI {
public:
	static void Init();

	static void* ReadSplittedAI(const wchar_t *filename, UINT32 *filesize);

	static unsigned char *buffer;
};

