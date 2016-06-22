
#include "GraciaEpilogue.h"
#include "CUser.h"
#include "CLog.h"
#include "CYieldLock.h"
#include "CSharedCreatureData.h"

int __cdecl GraciaEpilogue::AssembleBuySellListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT64 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s)
{
	//                                abcdefghijklmnopqrs000
	return Assemble(buffer, maxSize, "hddQhhdhhhQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, 0, 0, 0);
}

namespace {
CUserSocket *UserSocketFromBuySell(UINT32 a)
{
	void *ret;
	reinterpret_cast<void*(*)(void*,void**,UINT32)>(0x448F14)(
		reinterpret_cast<void*>(0x10DE4580),
		&ret,
		a);
	if (!ret) {
		return 0;
	}
	ret = reinterpret_cast<void*(*)(void*)>(
		*reinterpret_cast<void**>(reinterpret_cast<char*>(*reinterpret_cast<void**>(ret)) + 0x1E0))(ret);
	if (!ret) {
		return 0;
	}
	ret = reinterpret_cast<void*(*)(void*)>(
		*reinterpret_cast<void**>(reinterpret_cast<char*>(*reinterpret_cast<void**>(ret)) + 0xAD0))(ret);
	return reinterpret_cast<CUserSocket*>(ret);
}
bool IsEconomySell(void *economy)
{
	bool ret = __RTtypeid(economy) == reinterpret_cast<std::type_info*>(0xE588D8);
	CLog::Add(CLog::Blue, L"IsEconomySell %p -> %p -> %d",
		economy, __RTtypeid(economy), ret ? 1 : 0);
	return ret;
}
bool IsEconomyBuy(void *economy)
{
	bool ret = __RTtypeid(economy) == reinterpret_cast<std::type_info*>(0xE588F8);
	CLog::Add(CLog::Blue, L"IsEconomyBuy %p -> %p -> %d",
		economy, __RTtypeid(economy), ret ? 1 : 0);
	return ret;
}
}

bool __cdecl GraciaEpilogue::NpcShowBuySellPagePacket(void *npcSocket, const BYTE *packet)
{
	typedef bool (__cdecl *t)(void*, const BYTE*);

	CUserSocket *userSocket = UserSocketFromBuySell(*reinterpret_cast<const UINT32*>(packet));
	if (!userSocket) {
		return false;
	}

	CUser *user = userSocket->user;
	if (!user) {
		return false;
	}

	if (packet[-1] == 0x9) { // buy
		user->sdLock->Enter(__FILEW__, __LINE__);
		if (user->economy && !IsEconomySell(user->economy)) {
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		void *tmp = user->economy;
		user->economy = user->ext.buySell.economy2;
		user->ext.buySell.economy2 = tmp;

		user->sdLock->Leave(__FILEW__, __LINE__);

		CLog::Add(CLog::Blue, L"Create buy list");

		if (reinterpret_cast<t>(0x746318)(npcSocket, packet)) {
			user->sdLock->Enter(__FILEW__, __LINE__);
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return true;
		}

		user->sdLock->Enter(__FILEW__, __LINE__);

		if (user->ext.buySell.economy2 && !IsEconomySell(user->ext.buySell.economy2)) {
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (!user->economy || !IsEconomyBuy(user->economy)) {
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		CLog::Add(CLog::Blue, L"Put buy list in economy2");

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
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		user->sdLock->Leave(__FILEW__, __LINE__);

		CLog::Add(CLog::Blue, L"Create sell list");

		if (reinterpret_cast<t>(0x747184)(npcSocket, packet)) {
			user->sdLock->Enter(__FILEW__, __LINE__);
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return true;
		}

		user->sdLock->Enter(__FILEW__, __LINE__);

		if (user->ext.buySell.economy2 && !IsEconomyBuy(user->ext.buySell.economy2)) {
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (!user->economy || !IsEconomySell(user->economy)) {
			CUserReleaseEconomy(user);
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

		if (!user->ext.buySell.economy2) {
			user->sdLock->Leave(__FILEW__, __LINE__);
			return false;
		}

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
}

void __cdecl GraciaEpilogue::UserShowHTMLAfterBuySell(CUser *user, const wchar_t *s1, const wchar_t *s2, unsigned int i)
{
	NpcSocketSendHtmlCmdMenuSelectFirst(
		user, "cddddQd", 0xC, user->sd->index, user->objectId, user->ext.buySell.storedNpcSdIndex,
		-1, user->ext.buySell.storedReply, -1, false);
}

void __cdecl GraciaEpilogue::SendBuySellWrapper(CUserSocket *socket, const unsigned char isBuy, unsigned char opcode, UINT64 adena, UINT32 buyListId, UINT16 itemCount, UINT32 size, void *data)
{
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
{
	CLog::Add(CLog::Blue, L"Release economy");
	typedef bool (__cdecl *t)(CUser*);
	t f = reinterpret_cast<t>(0x8D6A70);
	bool result = false;
	result = f(self);
	if (self->ext.buySell.economy2) {
		CLog::Add(CLog::Blue, L"Release economy2");
		self->economy = self->ext.buySell.economy2;
		self->ext.buySell.economy2 = 0;
		result |= f(self);
	}
	return result;
}

bool __cdecl GraciaEpilogue::SellPacket(CUserSocket *socket, const BYTE *packet, BYTE opcode)
{
	CUser *user = socket->user;
	if (!user) {
		return false;
	}

	if (*reinterpret_cast<const UINT32*>(packet) != user->ext.buySell.buyList.id) {
		return false;
	}

	*reinterpret_cast<UINT32*>(const_cast<BYTE*>(packet)) = user->ext.buySell.sellList.id;

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
{
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
	NpcSocketSendHtmlCmdMenuSelectFirst(user, format, opcode, userSdIndex, userObjectId, npcSdIndex, ask, reply, state, true);
}

void __cdecl GraciaEpilogue::NpcSocketSendHtmlCmdMenuSelectFirst(CUser *user, const char *format, BYTE opcode, UINT32 userSdIndex, UINT32 userObjectId, UINT32 npcSdIndex, INT32 ask, INT64 reply, INT32 state, bool first)
{
	void *npcSocket = reinterpret_cast<void*>(0x1634170);
	typedef void (__cdecl *t)(void*, const char*, BYTE, UINT32, UINT32, UINT32, INT32, INT64, INT32);
	t f = reinterpret_cast<t>(0x72D09C);
	if (ask != -1 || state != -1 || reply > 8) {
		f(npcSocket, format, opcode, userSdIndex, userObjectId, npcSdIndex, ask, reply, state);
		return;
	}

	if (!user) {
		return;
	}

	user->sdLock->Enter(__FILEW__, __LINE__);

	CUserReleaseEconomy(user);
	user->ext.buySell.fakeSell = reply == 8;
	user->ext.buySell.firstBuySell = first;
	user->ext.buySell.storedReply = reply;
	user->ext.buySell.storedNpcSdIndex = npcSdIndex;
	user->ext.buySell.buySellSwitched = false;

	user->sdLock->Leave(__FILEW__, __LINE__);

	f(npcSocket, format, opcode, userSdIndex, userObjectId, npcSdIndex, ask, reply, state);
	if (reply < 8) {
		f(npcSocket, format, opcode, userSdIndex, userObjectId, npcSdIndex, ask, 8, state);
	}
}

