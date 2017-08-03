
#include <Server/NpcServer.h>
#include <Server/CCreature.h>
#include <Server/CNPC.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/GraciaEpilogue.h>
#include <NPCd/NPCd.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/CSharedCreatureData.h>
#include <Common/SmartPtr.h>

void NpcServer::Init()
{
	WriteMemoryBYTES(0x74B579, "\x48\x8B\x94\x24\xA0\x00\x00\x00\x48\x8B\x8C\x24\xB0\x42\x00\x00", 16);
	WriteInstructionCall(0x74B589, reinterpret_cast<UINT32>(SendCreateOnePrivateNearUserWrapper), 0x74B591);
	WriteAddress(0xA2742B, reinterpret_cast<UINT32>(NpcEx));
}

NpcServer::NpcServer()
{
}

NpcServer::NpcServer(const NpcServer &other)
{
}

NpcServer::~NpcServer()
{
}

NpcServer* NpcServer::Instance()
{
	return reinterpret_cast<NpcServer*>(0x1634170);
}

void* NpcServer::GetSocket()
{
	return reinterpret_cast<void*(*)(void*)>(0x72CD10)(this);
}

void NpcServer::Send(const char *format, ...)
{
	GUARDED;

	va_list va;
	va_start(va, format);
	SendV(format, va);
	va_end(va);
}

void NpcServer::SendV(const char *format, va_list va)
{
	void *socket = GetSocket();
	if (!socket) {
		CLog::Add(CLog::Red, L"Attempt to write to null socket!");
		return;
	}
	reinterpret_cast<void(*)(void*, const char*, va_list)>(0x859934)(socket, format, va);
}

void __cdecl NpcServer::SendCreateOnePrivateNearUserWrapper(void *self, CCreature *creature, BYTE unused, UINT32 a, UINT32 b, UINT64 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h, UINT32 i, UINT32 j, UINT32 k, wchar_t *l, UINT32 m, UINT32 n, void *o, UINT32 p)
{
	Instance()->Send("cddpddddddddSdbdd", 0x98, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, creature->sd->inZoneId);
}

bool NpcServer::NpcEx(void *socket, const unsigned char *bytes)
{
	const unsigned char *data = &bytes[2];
	switch (*reinterpret_cast<const UINT16*>(bytes)) {
	case NPCd::WHISPER: return NpcWhisper(socket, data);
	case NPCd::SET_ABILITY_ITEM_DROP: return NpcSetAbilityItemDrop(socket, data);
	case NPCd::SHOW_BUY_SELL: return NpcShowBuySell(socket, data);
	}
	return true;
}

bool NpcServer::NpcWhisper(void *socket, const unsigned char *bytes)
{
	UINT32 npcIndex;
	UINT32 talkerIndex;
	wchar_t text[1024];

	Disassemble(bytes, "ddS", &npcIndex, &talkerIndex, sizeof(text) / sizeof(text[0]), text);

	SmartPtr<CCreature> npc(npcIndex);
	SmartPtr<CCreature> talker_(talkerIndex);
	if (!npc || !talker_ || !talker_->IsUser()) {
		return false;
	}

	CUser &talker = reinterpret_cast<CUser&>(*talker_);
	CUserSocket *userSocket = talker.socket;
	if (userSocket) {
		userSocket->Send("cdddS", 0x30, npc->objectId, 0, npc->objectType, text);
	}

	return false;
}

bool NpcServer::NpcSetAbilityItemDrop(void *socket, const unsigned char *bytes)
{
	UINT32 npcIndex;
	unsigned char value;
	wchar_t text[1024];

	Disassemble(bytes, "dc", &npcIndex, &value);

	SmartPtr<CCreature> npc(npcIndex);
	if (npc) {
		if (value) {
			npc->inventory.noDropItems &= 1;
		} else {
			npc->inventory.noDropItems |= 2;
		}
	}

	return false;
}

bool NpcServer::NpcShowBuySell(void *socket, const unsigned char *bytes)
{
	GUARDED;

	UINT32 npcIndex;
	UINT32 talkerIndex;
	UINT32 buyList;
	UINT32 sellList;
	float rate;

	Disassemble(bytes, "ddddf", &npcIndex, &talkerIndex, &buyList, &sellList, &rate);
	unsigned char buyBuffer[32];
	unsigned char sellBuffer[24];
	Assemble(reinterpret_cast<char*>(buyBuffer), sizeof(buyBuffer), "dddSSSf", talkerIndex, npcIndex, buyList, L"", L"", L"", rate);
	Assemble(reinterpret_cast<char*>(sellBuffer), sizeof(sellBuffer), "dddSSS", talkerIndex, npcIndex, sellList, L"", L"", L"");

	typedef bool (__cdecl *t)(void*, const BYTE*);

	SmartPtr<CUser> user(talkerIndex);
	if (!user || !user->IsUser()) {
		return false;
	}

	CUserSocket *userSocket = user->socket;
	if (!userSocket) {
		return false;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);
	GraciaEpilogue::CUserReleaseEconomy(&*user);
	user->sdLock->Leave(__FILEW__, __LINE__);

	if (reinterpret_cast<t>(0x747184)(socket, sellBuffer)) {
		return true;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);

	if (!user->economy) {
		GraciaEpilogue::CUserReleaseEconomy(&*user);
		user->sdLock->Leave(__FILEW__, __LINE__);
		return false;
	}

	void *tmp = user->economy;
	user->economy = user->ext.buySell.economy2;
	user->ext.buySell.economy2 = tmp;

	user->sdLock->Leave(__FILEW__, __LINE__);

	if (reinterpret_cast<t>(0x746318)(socket, buyBuffer)) {
		user->sdLock->Enter(__FILEW__, __LINE__);
		GraciaEpilogue::CUserReleaseEconomy(&*user);
		user->sdLock->Leave(__FILEW__, __LINE__);
		return true;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);

	if (!user->economy) {
		GraciaEpilogue::CUserReleaseEconomy(&*user);
		user->sdLock->Leave(__FILEW__, __LINE__);
		return false;
	}

	tmp = user->economy;
	user->economy = user->ext.buySell.economy2;
	user->ext.buySell.economy2 = tmp;

	userSocket->Send("chQdhbhbhc", 0xFE, 0xB7,
		user->ext.buySell.buyList.adena,
		user->ext.buySell.buyList.id,
		user->ext.buySell.sellList.itemCount,
		user->ext.buySell.sellList.items.size(),
		user->ext.buySell.sellList.items.data(),
		user->ext.buySell.buyList.itemCount,
		user->ext.buySell.buyList.items.size(),
		user->ext.buySell.buyList.items.data(),
		0,
		!user->ext.buySell.firstBuySell);

	user->ext.buySell.firstBuySell = false;

	user->sdLock->Leave(__FILEW__, __LINE__);

	return false;
}

