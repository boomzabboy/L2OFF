
#pragma once

#include <windows.h>
#include <string>

class BuilderCmd2Handler {
public:
	static void Init();
	static bool __cdecl Handler(class CUserSocket *socket, const BYTE *packet);
	static bool Say(class CUserSocket *socket, class CUser *user, class CCreature *target, const BYTE *packet, const std::wstring &buffer);
	static bool DropItemEach(class CUserSocket *socket, class CUser *user, class CCreature *target, const BYTE *packet, const std::wstring &buffer);
	static bool Give(class CUserSocket *socket, class CUser *user, class CCreature *target, const BYTE *packet, const std::wstring &buffer);
	static bool Take(class CUserSocket *socket, class CUser *user, class CCreature *target, const BYTE *packet, const std::wstring &buffer);
};

