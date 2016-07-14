
#include <Server/OlympiadFixes.h>
#include <Server/CUser.h>
#include <Common/Utils.h>

void OlympiadFixes::Init()
{
	WriteInstructionCall(0x7D96EB, reinterpret_cast<UINT32>(PledgeSkillLock));
	WriteInstructionCall(0x7D9737, reinterpret_cast<UINT32>(PledgeSkillLock));
}

void __cdecl OlympiadFixes::PledgeSkillLock(unsigned long &a, int b, CUser *user, bool d, bool e, bool &f)
{ GUARDED

	if (!user) {
		return;
	}
	if (user->IsInOlympiad()) {
		b = -1;
	}
	reinterpret_cast<void(*)(unsigned long&, int, CUser*, bool, bool, bool&)>(0x7CDB90)(a, b, user, d, e, f);
}


