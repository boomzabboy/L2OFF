
#pragma once

#include <windows.h>

class BuilderCmd2Handler {
public:
	static void Init();
	static bool __cdecl Handler(class CUserSocket *socket, const BYTE *packet);
};

