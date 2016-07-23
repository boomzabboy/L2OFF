
#pragma once

#include <windows.h>

class SkillEnchantFix {
public:
	static bool __cdecl RequestExEnchantSkillInfoDetail(class CUserSocket *self, const BYTE *packet, BYTE opcode);
};

