
#include <Server/SkillEnchantFix.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Common/Utils.h>

bool __cdecl SkillEnchantFix::RequestExEnchantSkillInfoDetail(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	GUARDED;

	(void) opcode;

	CUser *user = self->GetUser();
	if (!user) {
		return false;
	}

	UINT32 enchantType = 0;
	UINT32 skillId = 0;
	UINT32 skillLevel = 0;

	Disassemble(packet, "ddd", &enchantType, &skillId, &skillLevel);

	if (enchantType > 3) {
		return true;
	}

	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x91A734)(self, packet);
}

