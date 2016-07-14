
#pragma once

#include <windows.h>

class AugmentationStatFix {
public:
	static void Init();

	static BYTE* __cdecl Fix(BYTE *a, BYTE *b, int c, int d, int e, int f, int g, BYTE h);
};

