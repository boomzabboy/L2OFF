
#include <Server/GraciaEpilogue.h>
#include <Server/CUser.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CLog.h>

void GraciaEpilogue::Init()
{
	InitPackets();
	InitBuySell();
	InitSkillEnchant();
}

void GraciaEpilogue::Load()
{ GUARDED

	LoadSkillEnchant();
}

bool __cdecl GraciaEpilogue::DiagPacket(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	const UINT16 &packetLen(*reinterpret_cast<const UINT16*>(packet - 3));
	std::string data(reinterpret_cast<const char*>(packet), packetLen - 3);
	const wchar_t *username = L"UNKNOWN";
	CUser *user = self->user;
	if (user) {
		username = user->GetName();
	}
	CLog::Add(CLog::Blue, L"DiagPacket from user %s:", username);
	CLog::Add(CLog::Blue, L"%s", Widen(data).c_str());
	CLog::Add(CLog::Blue, L"--");
	return false;
}

