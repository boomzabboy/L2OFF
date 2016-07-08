
#include "CUser.h"
#include "CSharedCreatureData.h"
#include "Utils.h"
#include "Config.h"
#include "CUserSocket.h"
#include "CParty.h"
#include "CSummon.h"
#include <new>
#include <time.h>

CriticalSection CUser::counterCS;
size_t CUser::counterTotal = 0;
size_t CUser::counterOffline = 0;

CUser::CUser()
{
}

CUser::~CUser()
{
}

void CUser::Init()
{
	WriteMemoryDWORD(0x5AEF0E, sizeof(CUser));
	WriteMemoryDWORD(0x5E1869, sizeof(CUser));
	WriteInstruction(0x5E1ACA, reinterpret_cast<UINT32>(Constructor), 0xE8);
	WriteInstruction(0x8D4340, reinterpret_cast<UINT32>(Destructor), 0xE8);
	WriteMemoryQWORD(0xC54088, reinterpret_cast<UINT64>(SayWrapper));
	WriteMemoryQWORD(0xC54128, reinterpret_cast<UINT64>(ExpIncWrapper));
	WriteInstructionCall(0x487FCE, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x73731E, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x75CAF2, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x75EBB6, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x75ECFA, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x760700, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x83AE20, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x89EE61, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x8A191F, reinterpret_cast<UINT32>(AddVitalityPointWrapper));
	WriteInstructionCall(0x8CFE24, reinterpret_cast<UINT32>(AddVitalityPointWrapper));

	WriteMemoryQWORD(0xC546F8, reinterpret_cast<UINT64>(SendCharInfoWrapper));
	WriteInstructionCall(0x93A05C, reinterpret_cast<UINT32>(OfflineTradePartyInvite));
	WriteMemoryQWORD(0xC54400, reinterpret_cast<UINT64>(EnterWorldWrapper));

	WriteMemoryQWORD(0xc53f58, reinterpret_cast<UINT64>(IsEnemyToWrapper));
	WriteInstructionCall(0x52E43C + 0x164, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x569908 + 0x4DB, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x8CCEAC + 0x18D, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x8CD084 + 0x1E3, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x8CE2A4 + 0x9, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x8CFECC + 0x3C5, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x8D03B8 + 0x1EF, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x907EF0 + 0xC0, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x907EF0 + 0x40F, reinterpret_cast<UINT32>(GetRelationToWrapper));
	WriteInstructionCall(0x9084FC + 0x3C7, reinterpret_cast<UINT32>(GetRelationToWrapper));

	WriteMemoryQWORD(0xC545D0, reinterpret_cast<UINT64>(OnMagicSkillUsePacketWrapper));
	WriteMemoryBYTES(0x711CA8, "\x48\x89\xF9", 3);
	WriteInstructionCall(0x711CAB, reinterpret_cast<UINT32>(FixPendingSkill), 0x711CB9);

	WriteInstructionCall(0x8BD015, reinterpret_cast<UINT32>(IsInBlockListWrapper));

	WriteMemoryQWORD(0xC543F8, reinterpret_cast<UINT64>(DeleteItemInInventoryBeforeCommitWrapper));
}

CUser* __cdecl CUser::Constructor(CUser *self, wchar_t* characterName, wchar_t* accountName,
								  unsigned int characterId, unsigned int accountId,
								  unsigned int pledgeId, unsigned int builder,
								  unsigned int gender, unsigned int race,
								  unsigned int classId, unsigned int world,
								  int x, int y, int z, double hp, double mp,
								  unsigned int sp, unsigned __int64 exp, unsigned int level,
								  int align, unsigned int pk, unsigned int pvp, unsigned int pkPardon,
								  unsigned int uUnk1, unsigned int uUnk2, unsigned int uUnk3, unsigned int uUnk4,
								  unsigned int uUnk5, unsigned int uUnk6, unsigned int uUnk7, unsigned int uUnk8,
								  unsigned int uUnk9, wchar_t *characterTitle, unsigned char *pUnkBuff, unsigned int uUnk10,
								  unsigned int uUnk11, unsigned int uUnk12, unsigned int uUnk13, unsigned int uUnk14,
								  unsigned int uUnk15, unsigned int uUnk16, unsigned int uUnk17, unsigned int uUnk18,
								  unsigned int uUnk19, unsigned int uUnk20, unsigned int uUnk21, unsigned int uUnk22, bool bUnk23)
{
	typedef CUser* (__cdecl *t)(CUser*, wchar_t*, wchar_t*, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								int, int, int, double, double, unsigned int, unsigned __int64, unsigned int,
								int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, wchar_t*, unsigned char*, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, bool);
	t f = reinterpret_cast<t>(0x8D435C);
	CUser *ret = f(self, characterName, accountName, characterId, accountId, pledgeId, builder, gender, race,
		classId, world, x, y, z, hp, mp, sp, exp, level, align, pk, pvp, pkPardon,
		uUnk1, uUnk2, uUnk3, uUnk4, uUnk5, uUnk6, uUnk7, uUnk8, uUnk9, characterTitle,
		pUnkBuff, uUnk10, uUnk11, uUnk12, uUnk13, uUnk14, uUnk15, uUnk16, uUnk17,
		uUnk18, uUnk19, uUnk20, uUnk21, uUnk22, bUnk23);
	new (&ret->ext) Ext();
	{
		ScopedLock lock(counterCS);
		++counterTotal;
	}
	return ret;
}

CUser* __cdecl CUser::Destructor(CUser *self, bool isMemoryFreeUsed)
{
	{
		ScopedLock lock(counterCS);
		--counterTotal;
		if (self->ext.isOffline) {
			--counterOffline;
		}
	}
	self->ext.~Ext();
	typedef CUser* (__cdecl *t)(CUser*, bool);
	t f = reinterpret_cast<t>(0x8D33C0);
	return f(self, isMemoryFreeUsed);
}

CUser::Ext::Ext() :
	isExpOff(false),
	isOffline(false)
{
}

CUser::Ext::~Ext()
{
}

CUser::Ext::BuySell::BuySell() :
	economy2(0),
	storedNpcSdIndex(0),
	storedReply(-1),
	firstBuySell(true),
	fakeSell(false)
{
}

CUser::Ext::BuySell::BuySellList::BuySellList() :
	adena(0),
	id(0),
	itemCount(0)
{
}

CUser::Ext::LastSkill::LastSkill() :
	skillId(0),
	firstFail(0),
	ctrl(false),
	shift(false)
{
}

CUser::Ext::Guard::Guard() :
	lastDropItem(0),
	lastChangeItem(0),
	isEnchanting(false),
	hasEnteredWorld(false)
{
}

UINT64 CUser::GetItemCount(UINT32 itemId)
{
	return reinterpret_cast<UINT64(*)(void*, UINT32, int)>(0x6864B4)(
		reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0xaa8), itemId, 0);
}

void CUser::TakeItem(UINT32 itemId, UINT64 count)
{
	reinterpret_cast<void(*)(CUser*, UINT32, UINT64, int)>(
		*reinterpret_cast<void**>(
			reinterpret_cast<char*>(*reinterpret_cast<void**>(this)) + 0x830))(
				this, itemId, count, 0);
}

CParty* CUser::GetParty()
{
	return reinterpret_cast<CParty*(*)(CUser*)>(0x8A1C40)(this);
}

void CUser::ResetNicknameAndColor()
{
	reinterpret_cast<void(*)(CUser*)>(0x89F354)(this);
}

void __cdecl CUser::SayWrapper(CUser *self, const wchar_t *message)
{
	if (message[0] != L'.' || !Config::Instance()->voiceCommands->enabled) {
		self->Say(message);
		return;
	}

	std::wstring command = message + 1;
	if (command == L"expoff" && Config::Instance()->voiceCommands->expOnOff) {
		if (!self->ext.isExpOff) {
			self->ext.isExpOff = true;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Experience gain turned off");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Experience gain already turned off");
		}
	} else if (command == L"expon" && Config::Instance()->voiceCommands->expOnOff) {
		if (self->ext.isExpOff) {
			self->ext.isExpOff = false;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Experience gain turned on");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Experience gain already turned on");
		}
	} else if (command == L"online" && Config::Instance()->voiceCommands->online) {
		wchar_t buffer[1024];
		if (Config::Instance()->voiceCommands->offline) {
			swprintf_s(buffer, 1024, L"There are %d characters online (%d on offline trade)", counterTotal, counterOffline);
		} else {
			swprintf_s(buffer, 1024, L"There are %d characters online", counterTotal);
		}
		self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), buffer);
	} else if (command == L"offline" && Config::Instance()->voiceCommands->offline) {
		self->StartOfflineTrade();
	} else if (command == L"time" && Config::Instance()->voiceCommands->time) {
		wchar_t buffer[1024];
		time_t now;
		time(&now);
		struct tm t;
		localtime_s(&t, &now);
		wcsftime(buffer, 1024, L"Current date and time is %Y-%m-%d %H:%M:%S", &t);
		self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), buffer);
	} else {
		self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Available voice commands:");
		if (Config::Instance()->voiceCommands->expOnOff) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".expon - turns experience gain on");
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".expoff - turns experience gain off");
		}
		if (Config::Instance()->voiceCommands->online) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".online - shows online player count");
		}
		if (Config::Instance()->voiceCommands->offline) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".offline - start offline trade mode");
		}
		if (Config::Instance()->voiceCommands->time) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".time - show current server time");
		}
	}
}

void CUser::Say(const wchar_t *message)
{
	reinterpret_cast<void(*)(CUser*, const wchar_t*)>(0x8AB200)(this, message);
}

INT64 __cdecl CUser::ExpIncWrapper(CUser *self, const INT64 exp, const bool b)
{
	return self->ExpInc((exp < 0 || !self->ext.isExpOff) ? exp : 0, b);
}

INT64 CUser::ExpInc(const INT64 exp, const bool b)
{
	return reinterpret_cast<INT64(*)(CUser*, const INT64, const bool)>(0x88BF30)(this, exp, b);
}

void __cdecl CUser::AddVitalityPointWrapper(CUser *self, const int points, const int type, const bool b)
{
	int points_ = points;
	if (points_ < 0) {
		if (!self->ext.isExpOff) {
			points_ = static_cast<int>(points * Config::Instance()->server->vitalityMultiplier);
		} else {
			points_ = 0;
		}
	}

	if (Config::Instance()->fixes->maxReplenishedVitalityPoints >= 0 && type == 6 && points < 0 && self->isVitalityReplenishing > 0) {
		if (points_ < -Config::Instance()->fixes->maxReplenishedVitalityPoints) {
			points_ = -Config::Instance()->fixes->maxReplenishedVitalityPoints;
		}
	}

	self->AddVitalityPoint(points_, type, b);
}

void CUser::AddVitalityPoint(const int points, const int type, const bool b)
{
	reinterpret_cast<void(*)(CUser*, const int, const int, const bool)>(0x89C918)(this, points, type, b);
}

void CUser::StartOfflineTrade()
{
	switch (sd->storeMode) {
	case 1:	case 3:	case 5:	case 8: break;
	default:
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"You can use offline store only when trading");
		return;
	}

	CParty *party = GetParty();
	if (party) {
		party->Withdraw(this, true);
	}

	*reinterpret_cast<void**>(socket) = CUserSocket::offlineTradeVtable;

	Sleep(500);

	socket->ext.offlineUser = this;
	socket->Close();
	socket->user = this;
	socket->ext.offlineSocketHandleCopy = 0;

	acceptPM = false;
	nickColor = 0x7f7f7f;
	ResetNicknameAndColor();
	ext.isOffline = true;

	{
		ScopedLock lock(counterCS);
		++counterOffline;
	}
}

void* __cdecl CUser::OfflineTradePartyInvite(void *a, void *b, void *c)
{
	void *ret = reinterpret_cast<void*(*)(void*, void*, void*)>(0x4CEDAC)(a, b, c);
	if (ret && *reinterpret_cast<UINT64*>(ret) && **reinterpret_cast<UINT64**>(ret) == 0xC53BB8) {
		CUser **user = reinterpret_cast<CUser**>(ret);
		if ((*user)->ext.isOffline) {
			*user = 0; // invalid target
		}
	}
	return ret;
}

void __cdecl CUser::SendCharInfoWrapper(CUser *self, CUserSocket *socket, const bool b)
{
	self->SendCharInfo(socket, b);
	if (self->ext.isOffline) {
		switch (self->sd->storeMode) {
		case 1:	case 3:	case 5:	case 8:
			return;
		default:
			break;
		}

		CUserSocket *socket2 = self->socket;
		socket2->ext.offlineUser = 0;
		socket2->user = self;
		socket2->OnClose();
	}
}

void CUser::SendCharInfo(CUserSocket *socket, const bool b)
{
	reinterpret_cast<void(*)(CUser*, CUserSocket*, const bool)>(0x90C3E0)(this, socket, b);
}

void __cdecl CUser::EnterWorldWrapper(CUser *self)
{
	self->EnterWorld();
	if (self->sd->builder) {
		self->nickColor = 0xff00;
		self->ResetNicknameAndColor();
		reinterpret_cast<bool(*)(CUserSocket*, CUser*, wchar_t*)>(0x48A8EC)(self->socket, self, L"//gmon");
	}
}

void CUser::EnterWorld()
{
	reinterpret_cast<void(*)(CUser*)>(0x8CF0E4)(this);
}

CMultiPartyCommandChannel* CUser::GetMPCC()
{
	return reinterpret_cast<CMultiPartyCommandChannel*(*)(CUser*)>(0x8A600C)(this);
}

void CUser::SendRelationChanged(CUserSocket *socket)
{
	reinterpret_cast<void(*)(CUser*, CUserSocket*)>(0x907EF0)(this, socket);
}

bool __cdecl CUser::IsEnemyToWrapper(CUser *self, CCreature *creature)
{
	return self->IsEnemyTo(creature);
}

bool CUser::IsEnemyTo(CCreature *creature)
{
	bool ret = reinterpret_cast<bool(*)(CUser*, CCreature*)>(0x8CD084)(this, creature);

	if (!Config::Instance()->fixes->commandChannelFriendly) {
		return ret;
	}

	CParty *party = GetParty();
	CMultiPartyCommandChannel *channel = GetMPCC();

	if (creature->IsUser()) {
		CUser *targetUser = reinterpret_cast<CUser*>(creature);
		if (targetUser == this) {
			ret = false;
		} else if (party && targetUser->GetParty() == party) {
			ret = false;
		} else if (channel && targetUser->GetMPCC() == channel) {
			ret = false;
		}
		return ret;
	}

	if (creature->IsSummon()) {
		CSummon *summon = reinterpret_cast<CSummon*>(creature);
		CUser *owner = summon->GetUserOrMaster();
		if (owner) {
			if (owner == this) {
				ret = false;
			} else if (party && owner->GetParty() == party) {
				ret = false;
			} else if (channel && owner->GetMPCC() == channel) {
				ret = false;
			}
		}
		return ret;
	}

	return ret;
}

int CUser::GetRelationTo(CUser *user)
{
	int ret = reinterpret_cast<int(*)(CUser*, CUser*)>(0x8CC944)(this, user);

	if (!Config::Instance()->fixes->commandChannelFriendly) {
		return ret;
	}

	if (!(ret & 0x20)) {
		if (GetParty()) {
			CMultiPartyCommandChannel *channel = GetMPCC();
			if (channel && user->GetMPCC() == channel) {
				ret |= 0x20;
			}
		}
	}

	return ret;
}

int __cdecl CUser::GetRelationToWrapper(CUser *self, CUser *user)
{
	return self->GetRelationTo(user);
}

bool __cdecl CUser::OnMagicSkillUsePacketWrapper(CUser *self, int skillId, bool ctrl, bool shift)
{
	return self->OnMagicSkillUsePacket(skillId, ctrl, shift);
}

bool CUser::OnMagicSkillUsePacket(int skillId, bool ctrl, bool shift)
{
	ext.lastSkill.skillId = skillId;
	ext.lastSkill.ctrl = ctrl;
	ext.lastSkill.shift = shift;
	ext.lastSkill.firstFail = 0;
	return OnMagicSkillUsePacketOriginal(skillId, ctrl, shift);
}

bool CUser::OnMagicSkillUsePacketOriginal(int skillId, bool ctrl, bool shift)
{
	return reinterpret_cast<bool(*)(CUser*, int, bool, bool)>(0x8AD2E8)(this, skillId, ctrl, shift);
}

void __cdecl CUser::FixPendingSkill(CUser *user)
{
	if (Config::Instance()->fixes->repeatSkillOnDistanceFailSeconds < 0 || !user->ext.lastSkill.skillId) {
		CUserSocket *socket = user->socket;
		if (socket) {
			socket->SendSystemMessage(0x2EC);
		}
		return;
	}

	user->OnMagicSkillUsePacketOriginal(
		user->ext.lastSkill.skillId,
		user->ext.lastSkill.ctrl,
		user->ext.lastSkill.shift);

	UINT32 now = GetTickCount();

	if (!user->ext.lastSkill.firstFail) {
		user->ext.lastSkill.firstFail = now;
	} else if (user->ext.lastSkill.firstFail <= now - Config::Instance()->fixes->repeatSkillOnDistanceFailSeconds * 1000) {
		user->ext.lastSkill.skillId = 0;
	}
}

bool __cdecl CUser::IsInBlockListWrapper(CUser *self, int id)
{
	return self->IsInBlockList(id);
}

bool CUser::IsInBlockList(int id)
{
	if (IsInBlockListOriginal(id)) {
		return true;
	}
	if (Config::Instance()->fixes->disallowTradeInOlympiad && IsInOlympiad()) {
		return true;
	}
	return false;
}

bool CUser::IsInBlockListOriginal(int id)
{
	return reinterpret_cast<bool(*)(CUser*, int)>(0x8B4864)(this, id);
}

bool CUser::IsWaitingForOlympiad() const
{
	return olympiadStatus == 5;
}

bool CUser::IsInOlympiad() const
{
	return olympiadStatus == 1 || olympiadStatus == 2;
}

bool __cdecl CUser::DeleteItemInInventoryBeforeCommitWrapper(CUser *self, const UINT32 itemId, const UINT64 itemCount)
{
	return self->DeleteItemInInventoryBeforeCommit(itemId, itemCount);
}

bool CUser::DeleteItemInInventoryBeforeCommit(const UINT32 itemId, const UINT64 itemCount)
{
	if (IsNowTrade()) {
		return false;
	}
	return reinterpret_cast<bool(*)(CUser*, UINT32, UINT64)>(0x8E8D54)(this, itemId, itemCount);
}

bool CUser::IsNowTrade() const
{
	return reinterpret_cast<bool(*)(const CUser*)>(0x8A4E8C)(this);
}

CompileTimeOffsetCheck(CUser, acceptPM, 0x35D8);
CompileTimeOffsetCheck(CUser, padding0x35D9, 0x35D9);
CompileTimeOffsetCheck(CUser, isVitalityReplenishing, 0x38B0);
CompileTimeOffsetCheck(CUser, ext, 0x3A10);
