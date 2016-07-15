
#pragma once

#include <windows.h>

class Function {
public:
	static void Init();

	struct Remapped {
		UINT64 a;
		UINT64 b;
		UINT64 c;
	};

	static Remapped* __cdecl Remap(const UINT32 id);
};

