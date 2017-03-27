
#include <Server/GraciaEpilogue.h>
#include <Server/CUser.h>
#include <Server/CShortCut.h>
#include <Common/CLog.h>
#include <Common/CYieldLock.h>
#include <Common/CSharedCreatureData.h>
#include <Common/SmartPtr.h>

void GraciaEpilogue::InitBuySell()
{
	WriteAddress(0xA26CD0+3, reinterpret_cast<UINT32>(NpcShowBuySellPagePacket));
	WriteAddress(0xA26CA8+3, reinterpret_cast<UINT32>(NpcShowBuySellPagePacket));
	WriteMemoryBYTES(0x747E9B, "\x48\x8B\xCB\x48\x31\xD2\x90\x90\x90\x90\x90\x90\x90\x90", 14);
	WriteInstructionCall(0x747E9B+6, reinterpret_cast<UINT32>(SendBuySellWrapper));
	WriteMemoryBYTES(0x746EF6, "\x48\x31\xD2\x48\xFF\xC2\x90\x90\x90\x90\x90", 11);
	WriteInstructionCall(0x746EF6+6, reinterpret_cast<UINT32>(SendBuySellWrapper));
	WriteInstructionCall(0x747C48, reinterpret_cast<UINT32>(AssembleBuySellListItem));
	WriteInstructionCall(0x746C42, reinterpret_cast<UINT32>(AssembleBuySellListItem));
	WriteInstructionCall(0x5B6388, reinterpret_cast<UINT32>(UserShowHTMLAfterBuySell));
	WriteInstructionCall(0x5B5B42, reinterpret_cast<UINT32>(UserShowHTMLAfterBuySell));
    WriteInstructionCall(0x5B4B14 + 0x18A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B4B14 + 0x249, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B4B14 + 0x4C7, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B504C + 0x17F, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B504C + 0x5B2, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B5678 + 0x485, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B5BD0 + 0x74E, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C48B4 + 0x1AF, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C48B4 + 0x790, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C50E0 + 0x205, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C50E0 + 0x7D8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    //WriteInstructionCall(0x746318 + 0x3E2, reinterpret_cast<UINT32>(CUserReleaseEconomy)); // not this one
    //WriteInstructionCall(0x747184 + 0x3E7, reinterpret_cast<UINT32>(CUserReleaseEconomy)); // not this one
    WriteInstructionCall(0x748200 + 0x39A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x8CB090 + 0x525, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x8F2244 + 0x87, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x91D6C0 + 0x266, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x91D9C8 + 0x46A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x92F924 + 0x1647, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x931090 + 0xCDA, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x93276C + 0x681, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x945A6C + 0x485, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946018 + 0x470, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x9465A4 + 0x3E8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946AB0 + 0x3F8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946FCC + 0x2CD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x947398 + 0x2ED, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x9477A4 + 0x2F9, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x947BC0 + 0x2F9, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95C039, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95C97D, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95CC68, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95CFDB, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95D1DD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95D452, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95DA32, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E29D, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E57B, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E8F3, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95EAFA, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95ED40, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95F0DD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95F930, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95FD93, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95FF83, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960633, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960A9F, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960CA0, reinterpret_cast<UINT32>(CUserReleaseEconomy));
	WriteMemoryBYTES(0x94B1F3, "\x48\x89\xF1\x90\x90\x90\x90", 7); // mov rcx, rsi - get CUser* in rcx
	WriteInstructionCall(0x94B1FA, reinterpret_cast<UINT32>(NpcSocketSendHtmlCmdMenuSelect));
	WriteMemoryBYTE(0x5B5B69 + 2, 0); // don't show inventory after buy
	WriteMemoryBYTE(0x5B5B7A + 2, 0); // don't show inventory after buy
	WriteMemoryBYTE(0x5B63B3 + 2, 0); // don't show inventory after sell
	WriteMemoryBYTE(0x5B63C4 + 2, 0); // don't show inventory after sell

	// retain user pointer in rbx
	WriteMemoryBYTES(0x6CAF58,
		/* 6CAF58 */ "\x44\x8B\xC7"                     // mov r8d, edi
		/* 6CAF5B */ "\x48\x8D\x54\x24\x58"             // lea rdx, [rsp+0x58]
		/* 6CAF60 */ "\x48\x8D\x0D...."                 // lea rcx, ....
		/* 6CAF67 */ "....."                            // call 0x448F14
		/* 6CAF6C */ "\x90"                             // nop
		/* 6CAF6D */ "\x48\x8B\x83\x90\x0A\x00\x00"     // mov rax, [rbx+0xA90]
		/* 6CAF74 */ "\x44\x8B\x40\x28"                 // mov r8d, [rax+0x28]
		/* 6CAF78 */ "\x90\x90"                         // nop nop
		/* 6CAF7A */ , 0x6CAF7A - 0x6CAF58);
	WriteAddress(0x6CAF63, 0x10DE4580); // address to load to rcx above
	WriteInstructionCall(0x6CAF67, 0x448F14); // call 0x448F14 above
	WriteMemoryBYTES(0x6CAFDB, "\x49\x89\xD9", 3); // mov r9, rbx (instead of mov r9d, ebx)
	WriteInstructionCall(0x6CAFF2, reinterpret_cast<UINT32>(NpcSocketSendHtmlCmdManorMenuSelect));
}

int __cdecl GraciaEpilogue::AssembleBuySellListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT64 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s)
{
	//                                abcdefghijklmnopqrs000
	return Assemble(buffer, maxSize, "hddQhhdhhhQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, 0, 0, 0);
}

bool IsEconomySell(void *economy)
{
	bool ret = __RTtypeid(economy) == reinterpret_cast<std::type_info*>(0xE588D8);
	return ret;
}

bool IsEconomyBuy(void *economy)
{
	bool ret = __RTtypeid(economy) == reinterpret_cast<std::type_info*>(0xE588F8);
	return ret;
}

bool __cdecl GraciaEpilogue::NpcShowBuySellPagePacket(void *npcSocket, const BYTE *packet)
{
	GUARDED;

	typedef bool (__cdecl *t)(void*, const BYTE*);

	SmartPtr<CUser> user(*reinterpret_cast<const UINT32*>(packet));
	if (!user || !user->IsUser()) {
		return false;
	}

	CUserSocket *userSocket = user->socket;
	if (!userSocket) {
		return false;
	}

	if (packet[-1] == 0x9) { // buy
		user->sdLock->Enter(__FILEW__, __LINE__);
		if (user->economy && !IsEconomySell(user->economy)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		void *tmp = user->economy;
		user->economy = user->ext.buySell.economy2;
		user->ext.buySell.economy2 = tmp;

		user->sdLock->Leave(__FILEW__, __LINE__);

		if (reinterpret_cast<t>(0x746318)(npcSocket, packet)) {
			user->sdLock->Enter(__FILEW__, __LINE__);
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return true;
		}

		user->sdLock->Enter(__FILEW__, __LINE__);

		if (user->ext.buySell.economy2 && !IsEconomySell(user->ext.buySell.economy2)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (!user->economy || !IsEconomyBuy(user->economy)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		tmp = user->economy;
		user->economy = user->ext.buySell.economy2;
		user->ext.buySell.economy2 = tmp;

		if (!user->economy && !user->ext.buySell.fakeSell) {
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (user->ext.buySell.fakeSell) {
			userSocket->Send("chQdhhbhc", 0xFE, 0xB7,
				user->ext.buySell.buyList.adena,
				user->ext.buySell.buyList.id,
				0,
				user->ext.buySell.buyList.itemCount,
				user->ext.buySell.buyList.items.size(),
				user->ext.buySell.buyList.items.data(),
				0,
				!user->ext.buySell.firstBuySell);
		} else {
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
		}

		user->ext.buySell.firstBuySell = false;

		user->sdLock->Leave(__FILEW__, __LINE__);

		return false;
	} else {
		user->sdLock->Enter(__FILEW__, __LINE__);
		if (user->ext.buySell.economy2 && !IsEconomyBuy(user->ext.buySell.economy2)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		user->sdLock->Leave(__FILEW__, __LINE__);

		if (reinterpret_cast<t>(0x747184)(npcSocket, packet)) {
			user->sdLock->Enter(__FILEW__, __LINE__);
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return true;
		}

		user->sdLock->Enter(__FILEW__, __LINE__);

		if (user->ext.buySell.storedAsk != -1 || user->ext.buySell.storedState != -1 || user->ext.buySell.storedReply > 8) {
			userSocket->Send("chQdhbhhc", 0xFE, 0xB7,
			user->ext.buySell.sellList.adena,
			user->ext.buySell.sellList.id,
			user->ext.buySell.sellList.itemCount,
			user->ext.buySell.sellList.items.size(),
			user->ext.buySell.sellList.items.data(),
			0,
			0,
			!user->ext.buySell.firstBuySell);

			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (user->ext.buySell.economy2 && !IsEconomyBuy(user->ext.buySell.economy2)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (!user->economy || !IsEconomySell(user->economy)) {
			CUserReleaseEconomy(&*user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		void *npcSocket = reinterpret_cast<void*>(0x1634170);
		typedef void (__cdecl *t)(void*, const char*, BYTE, UINT32, UINT32, UINT32, INT32, INT64, INT32);
		t f = reinterpret_cast<t>(0x72D09C);
		f(npcSocket, "cddddQd", 0xC, user->sd->index, user->objectId, user->ext.buySell.storedNpcSdIndex, -1, 8, -1);

		user->sdLock->Leave(__FILEW__, __LINE__);

		return false;
	}
}

void __cdecl GraciaEpilogue::UserShowHTMLAfterBuySell(CUser *user, const wchar_t *s1, const wchar_t *s2, unsigned int i)
{
	GUARDED;

	if (!user) {
		return;
	}
	user->shortCut.SendShortCutInfo();
	NpcSocketSendHtmlCmdMenuSelectFirst(
		user, "cddddQd", 0xC, user->sd->index, user->objectId, user->ext.buySell.storedNpcSdIndex,
		user->ext.buySell.storedAsk, user->ext.buySell.storedReply, user->ext.buySell.storedState, false);
}

void __cdecl GraciaEpilogue::SendBuySellWrapper(CUserSocket *socket, const unsigned char isBuy, unsigned char opcode, UINT64 adena, UINT32 buyListId, UINT16 itemCount, UINT32 size, void *data)
{ GUARDED

	CUser *user = socket->user;
	if (!user) {
		return;
	}
	CUser::Ext::BuySell::BuySellList &list(isBuy ? user->ext.buySell.buyList : user->ext.buySell.sellList);
	list.adena = adena;
	list.id = buyListId;
	list.itemCount = itemCount;
	list.items = std::string(reinterpret_cast<const char*>(data), size);
}

bool __cdecl GraciaEpilogue::CUserReleaseEconomy(CUser *self)
{ GUARDED

	typedef bool (__cdecl *t)(CUser*);
	t f = reinterpret_cast<t>(0x8D6A70);
	bool result = false;
	result = f(self);
	if (self->ext.buySell.economy2) {
		self->economy = self->ext.buySell.economy2;
		self->ext.buySell.economy2 = 0;
		result |= f(self);
	}
	return result;
}

bool __cdecl GraciaEpilogue::SellPacket(CUserSocket *socket, const BYTE *packet, BYTE opcode)
{ GUARDED

	CUser *user = socket->user;
	if (!user) {
		return false;
	}

	if (*reinterpret_cast<const UINT32*>(packet) != user->ext.buySell.sellList.id) {
		if (*reinterpret_cast<const UINT32*>(packet) != user->ext.buySell.buyList.id || !user->ext.buySell.buyList.id) {
			return false;
		}
		*reinterpret_cast<UINT32*>(const_cast<BYTE*>(packet)) = user->ext.buySell.sellList.id;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);
	if (user->ext.buySell.buySellSwitched) {
		void *tmp = user->economy;
		user->economy = user->ext.buySell.economy2;
		user->ext.buySell.economy2 = tmp;
		user->ext.buySell.buySellSwitched = false;
	}
	user->sdLock->Leave(__FILEW__, __LINE__);

	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*, BYTE)>(0x92F924)(socket, packet, opcode);
}

bool __cdecl GraciaEpilogue::BuyPacket(CUserSocket *socket, const BYTE *packet, BYTE opcode)
{ GUARDED

	CUser *user = socket->user;
	if (!user) {
		return false;
	}

	if (*reinterpret_cast<const UINT32*>(packet) != user->ext.buySell.buyList.id) {
		return false;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);
	if (!user->ext.buySell.buySellSwitched) {
		void *tmp = user->economy;
		user->economy = user->ext.buySell.economy2;
		user->ext.buySell.economy2 = tmp;
		user->ext.buySell.buySellSwitched = true;
	}
	user->sdLock->Leave(__FILEW__, __LINE__);

	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*, BYTE)>(0x931090)(socket, packet, opcode);
}

void __cdecl GraciaEpilogue::NpcSocketSendHtmlCmdMenuSelect(CUser *user, const char *format, BYTE opcode, UINT32 userSdIndex, UINT32 userObjectId, UINT32 npcSdIndex, INT32 ask, INT64 reply, INT32 state)
{
	GUARDED;

	NpcSocketSendHtmlCmdMenuSelectFirst(user, format, opcode, userSdIndex, userObjectId, npcSdIndex, ask, reply, state, true);
}

void __cdecl GraciaEpilogue::NpcSocketSendHtmlCmdMenuSelectFirst(CUser *user, const char *format, BYTE opcode, UINT32 userSdIndex, UINT32 userObjectId, UINT32 npcSdIndex, INT32 ask, INT64 reply, INT32 state, bool first)
{
	GUARDED;

	void *npcSocket = reinterpret_cast<void*>(0x1634170);
	typedef void (__cdecl *t)(void*, const char*, BYTE, UINT32, UINT32, UINT32, INT32, INT64, INT32);
	t f = reinterpret_cast<t>(0x72D09C);

	if (!user) {
		return;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);
	CUserReleaseEconomy(user);
	user->ext.buySell.fakeSell = reply == 8;
	user->ext.buySell.firstBuySell = first;
	user->ext.buySell.storedAsk = ask;
	user->ext.buySell.storedReply = reply;
	user->ext.buySell.storedState = state;
	user->ext.buySell.storedNpcSdIndex = npcSdIndex;
	user->ext.buySell.buySellSwitched = false;
	user->sdLock->Leave(__FILEW__, __LINE__);
	f(npcSocket, format, opcode, userSdIndex, user->objectId, npcSdIndex, ask, reply, state);
}

void __cdecl GraciaEpilogue::NpcSocketSendHtmlCmdManorMenuSelect(void *npcSocket, const char *format, BYTE opcode, CUser *user, UINT32 npcSdIndex, INT32 ask, INT32 state, INT32 time)
{
	if (!user) {
		return;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);
	CUserReleaseEconomy(user);
	user->ext.buySell.fakeSell = false;
	user->ext.buySell.firstBuySell = true;
	user->ext.buySell.storedAsk = ask;
	user->ext.buySell.storedReply = 0;
	user->ext.buySell.storedState = state;
	user->ext.buySell.storedNpcSdIndex = npcSdIndex;
	user->ext.buySell.buySellSwitched = false;
	user->sdLock->Leave(__FILEW__, __LINE__);
	reinterpret_cast<void(*)(void*, const char*, BYTE, UINT32, UINT32, INT32, INT32, INT32)>(0x72D09C)(
		npcSocket, format, opcode, user->sd->index, npcSdIndex, ask, state, time);
}

