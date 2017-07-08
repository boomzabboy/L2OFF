
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/CParty.h>
#include <Server/CSummon.h>
#include <Server/Server.h>
#include <Server/CItem.h>
#include <Server/CDB.h>
#include <Server/CAttackAction.h>
#include <Server/CSkillAction2.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/Enum.h>
#include <Common/SmartPtr.h>
#include <new>
#include <sstream>
#include <fstream>
#include <time.h>

CriticalSection CUser::onlineOfflineTradeUsersCS;
std::set<CUser*> CUser::onlineUsers;
std::set<CUser*> CUser::offlineTradeUsers;
CriticalSection CUser::premiumIpAddressesCS;
std::map<UINT32, UINT32> CUser::premiumIpAddresses;

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
	WriteMemoryQWORD(0xC53BD8, reinterpret_cast<UINT64>(TimerExpiredWrapper));
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
	WriteInstructionCall(0x5E2048, reinterpret_cast<UINT32>(SetVitalityPointWrapper));
	WriteInstructionCall(0x89CA16, reinterpret_cast<UINT32>(SetVitalityPointWrapper));

	WriteMemoryQWORD(0xC546F8, reinterpret_cast<UINT64>(SendCharInfoWrapper));
	WriteInstructionCall(0x93A05C, reinterpret_cast<UINT32>(OfflineTradePartyInvite));
	WriteMemoryQWORD(0xC54400, reinterpret_cast<UINT64>(EnterWorldWrapper));
	WriteMemoryQWORD(0xC54408, reinterpret_cast<UINT64>(LeaveWorldWrapper));

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
	WriteInstructionCall(0x711CAB, reinterpret_cast<UINT32>(FixPendingSkill), 0x711CBA);

	WriteInstructionCall(0x8BD015, reinterpret_cast<UINT32>(IsInBlockListWrapper));

	WriteMemoryQWORD(0xC543F8, reinterpret_cast<UINT64>(DeleteItemInInventoryBeforeCommitWrapper));

	WriteInstructionCall(0x928850, reinterpret_cast<UINT32>(MultiSellChooseWrapper));

	WriteInstructionCall(0x471922, reinterpret_cast<UINT32>(GetPremiumLevelWrapper));
	WriteInstructionCall(0x971651, reinterpret_cast<UINT32>(GetPremiumLevelWrapper));

	bool ipBasedPremiumSystem = Config::Instance()->custom->ipBasedPremiumSystem;
	int ipBasedFixedPCCafePoints = Config::Instance()->custom->ipBasedFixedPCCafePoints;
	if (ipBasedPremiumSystem || ipBasedFixedPCCafePoints >= 0) {
		CreateThread(0, 0, PremiumIpRefresh, 0, 0, 0);
	}

	WriteInstructionCall(0x8DB130 + 0x69, reinterpret_cast<UINT32>(CanOpenPrivateShopWrapper));
	WriteInstructionCall(0x8DB1F8 + 0x69, reinterpret_cast<UINT32>(CanOpenPrivateShopWrapper));
	WriteInstructionCall(0x8DB2C0 + 0x69, reinterpret_cast<UINT32>(CanOpenPrivateShopWrapper));

	WriteInstructionCall(0x40DC24 + 0x176, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x44521C + 0x13A, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x44A364 + 0x112, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x4525C8 + 0x6FC, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x54C4FC + 0x22BB, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x62A69C + 0x6D1, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x665180 + 0x1DE, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x73A4A4 + 0x123, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x746318 + 0xB93, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x74D154 + 0x6A1, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x74D960 + 0x2DD, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x76F01C + 0xF7, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x7787D0 + 0x179, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x7E6D2C + 0x225, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x81B2CC + 0x20F, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x81B4EC + 0x223, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x94A098 + 0x39B, reinterpret_cast<UINT32>(ShowHTMLWrapper));
	WriteInstructionCall(0x94A098 + 0x432, reinterpret_cast<UINT32>(ShowHTMLWrapper));

	WriteInstructionCall(0x445054 + 0x177, reinterpret_cast<UINT32>(ShowQuestHTMLWrapper));
	WriteInstructionCall(0x44A18C + 0x116, reinterpret_cast<UINT32>(ShowQuestHTMLWrapper));

	WriteInstructionCall(0x8B15F4 + 0x24C, reinterpret_cast<UINT32>(IsValidPrivateStoreItemWrapper));
	WriteInstructionCall(0x8B15F4 + 0x563, reinterpret_cast<UINT32>(IsValidPrivateStoreItemWrapper));

	WriteInstructionCall(0x54033B, reinterpret_cast<UINT32>(OutOfSightWrapper), 0x540341);

	WriteInstructionCall(0x5A71E4, reinterpret_cast<UINT32>(SetPointWrapperOnLoad));
	WriteInstructionCall(0x5A7264 + 0x303, reinterpret_cast<UINT32>(SetPointWrapper));
	WriteInstructionCall(0x891F90 + 0x73, reinterpret_cast<UINT32>(SetPointWrapper));
	WriteInstructionCall(0x89C3A4 + 0xFF, reinterpret_cast<UINT32>(SetPointWrapper));
	WriteInstructionCall(0x89C66C + 0xAC, reinterpret_cast<UINT32>(SetPointWrapper));
	WriteInstructionCall(0x89CBC4 + 0x8D, reinterpret_cast<UINT32>(SetPointWrapper));
	WriteInstructionCall(0x5A7264 + 0x202, reinterpret_cast<UINT32>(AddPointWrapper));
	WriteInstructionCall(0x5A7264 + 0x2AE, reinterpret_cast<UINT32>(AddPointWrapper));
	WriteInstructionCall(0x8A1984 + 0x122, reinterpret_cast<UINT32>(AddPointWrapper));

	WriteInstructionCall(0x6B38B0 + 0x117, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B38B0 + 0x132, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B38B0 + 0x14D, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B38B0 + 0x168, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B38B0 + 0x183, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B3C28 + 0x92, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B3C28 + 0xC2, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B3C28 + 0xF2, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B3C28 + 0x122, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B3C28 + 0x152, reinterpret_cast<UINT32>(SetMessage_dWrapper));
	WriteInstructionCall(0x6B38B0 + 0xFC, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B38B0 + 0x248, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B38B0 + 0x2A5, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x226, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x296, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x2B1, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x2E2, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x313, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x384, reinterpret_cast<UINT32>(SetMessageVWrapper));
	WriteInstructionCall(0x6B3C28 + 0x39F, reinterpret_cast<UINT32>(SetMessageVWrapper));

	WriteInstructionCall(0x68DF4A, reinterpret_cast<UINT32>(GetObjectTradeFix));

	WriteInstructionCall(0x737525, FnPtr(&CUser::SetDailyQuest));

	WriteInstructionCall(0x5B862E, FnPtr(&CUser::ReplyEnchantItem));

	WriteInstructionCall(0x75E845, FnPtr(CVitalityPointGetDecrementValue));
	WriteInstructionCall(0x75FB09, FnPtr(CVitalityPointGetDecrementValue));
}

DWORD CUser::PremiumIpRefresh(void *v)
{
	(void) v;
	const bool showTime = Config::Instance()->custom->ipBasedPremiumSystemShowTime;
	for (;;) {
		Sleep(15000);
		std::map<UINT32, UINT32> addresses;
		std::ifstream ifs("premiumip.dat", std::ios::binary);
		if (ifs) {
			for (;;) {
				if (ifs.eof()) {
					break;
				}
				UINT32 address = 0;
				UINT32 time = 0;
				ifs.read(reinterpret_cast<char*>(&address), 4);
				if (showTime) {
					ifs.read(reinterpret_cast<char*>(&time), 4);
				}
				if (address) {
					addresses.insert(std::pair<UINT32, UINT32>(address, time));
				}
			}
			ifs.close();
			ScopedLock lock(premiumIpAddressesCS);
			premiumIpAddresses = addresses;
		}
	}
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
{ GUARDED

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
	ret->ProcessPremium();
	return ret;
}

CUser* __cdecl CUser::Destructor(CUser *self, bool isMemoryFreeUsed)
{ GUARDED

	{
		ScopedLock lock(onlineOfflineTradeUsersCS);
		std::set<CUser*>::iterator i = onlineUsers.find(self);
		if (i != onlineUsers.end()) {
			onlineUsers.erase(i);
		} else {
			std::set<CUser*>::iterator i = offlineTradeUsers.find(self);
			if (i != offlineTradeUsers.end()) {
				offlineTradeUsers.erase(i);
			}
		}
	}

	self->ext.~Ext();
	typedef CUser* (__cdecl *t)(CUser*, bool);
	t f = reinterpret_cast<t>(0x8D33C0);
	return f(self, isMemoryFreeUsed);
}

CUser::Ext::Ext() :
	isExpOff(false),
	isPetExpOff(false),
	isOffline(false),
	autoloot(true),
	famePointLoaded(false)
{
}

CUser::Ext::~Ext()
{
}

CUser::Ext::BuySell::BuySell() :
	economy2(0),
	storedNpcSdIndex(0),
	storedAsk(-1),
	storedReply(-1),
	storedState(-1),
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
{ GUARDED

	return reinterpret_cast<UINT64(*)(void*, UINT32, int)>(0x6864B4)(
		reinterpret_cast<void*>(reinterpret_cast<char*>(this) + 0xaa8), itemId, 0);
}

bool CUser::TakeItem(UINT32 itemId, UINT64 count)
{
	GUARDED;

	return reinterpret_cast<bool(*)(CUser*, UINT32, UINT64, int)>(
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
	GUARDED;

	if (message[0] != L'.' || !Config::Instance()->voiceCommands->enabled || !message[1]) {
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
	} else if (command == L"petexpoff" && Config::Instance()->voiceCommands->petExpOnOff) {
		if (!self->ext.isPetExpOff) {
			self->ext.isPetExpOff = true;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Pet experience gain turned off");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Pet experience gain already turned off");
		}
	} else if (command == L"petexpon" && Config::Instance()->voiceCommands->petExpOnOff) {
		if (self->ext.isPetExpOff) {
			self->ext.isPetExpOff = false;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Pet experience gain turned on");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Pet experience gain already turned on");
		}
	} else if (command == L"online" && Config::Instance()->voiceCommands->online) {
		wchar_t buffer[1024];
		size_t online = 0;
		size_t offlineTrade = 0;
		{
			ScopedLock lock(onlineOfflineTradeUsersCS);
			online = onlineUsers.size();
			offlineTrade = offlineTradeUsers.size();
		}
		if (Config::Instance()->voiceCommands->offline) {
			swprintf_s(buffer, 1024, L"There are %d characters online (%d on offline trade)", online + offlineTrade, offlineTrade);
		} else {
			swprintf_s(buffer, 1024, L"There are %d characters online", online);
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
	} else if (command == L"looton" && Config::Instance()->voiceCommands->autoloot) {
		if (!self->ext.autoloot) {
			self->ext.autoloot = true;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Autoloot turned on");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Autoloot already turned on");
		}
	} else if (command == L"lootoff" && Config::Instance()->voiceCommands->autoloot) {
		if (self->ext.autoloot) {
			self->ext.autoloot = false;
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Autoloot turned off");
		} else {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Autoloot already turned off");
		}
	} else {
		self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Available voice commands:");
		if (Config::Instance()->voiceCommands->expOnOff) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".expon - turns experience gain on");
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".expoff - turns experience gain off");
		}
		if (Config::Instance()->voiceCommands->petExpOnOff) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".petexpon - turns pet experience gain on");
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".petexpoff - turns pet experience gain off");
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
		if (Config::Instance()->voiceCommands->autoloot) {
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".looton - turns autoloot on");
			self->socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L".lootoff - turns autoloot off");
		}
	}
}

void CUser::Say(const wchar_t *message)
{
	reinterpret_cast<void(*)(CUser*, const wchar_t*)>(0x8AB200)(this, message);
}

INT64 __cdecl CUser::ExpIncWrapper(CUser *self, const INT64 exp, const bool b)
{
	return self->ExpInc(exp, b);
}

INT64 CUser::ExpInc(const INT64 exp, const bool b)
{ GUARDED

	return reinterpret_cast<INT64(*)(CUser*, const INT64, const bool)>(0x88BF30)(
        this, (exp < 0 || !ext.isExpOff) ? exp : 0, b);
}

void __cdecl CUser::AddVitalityPointWrapper(CUser *self, const int points, const int type, const bool b)
{
	self->AddVitalityPoint(points, type, b);
}

void CUser::AddVitalityPoint(const int points, const int type, const bool b)
{
	GUARDED;

	if (Config::Instance()->custom->removeVitalitySystem) {
		return;
	}

	int points_ = points;
	if (points_ < 0) {
		if (!ext.isExpOff) {
			points_ = static_cast<int>(points * Config::Instance()->server->vitalityMultiplier);
		} else {
			points_ = 0;
		}
	}

	if (Config::Instance()->fixes->maxReplenishedVitalityPoints >= 0 && type == 6 && points < 0 && isVitalityReplenishing > 0) {
		if (points_ < -Config::Instance()->fixes->maxReplenishedVitalityPoints) {
			points_ = -Config::Instance()->fixes->maxReplenishedVitalityPoints;
		}
	}

	reinterpret_cast<void(*)(CUser*, const int, const int, const bool)>(0x89C918)(this, points_, type, b);
}

void __cdecl CUser::SetVitalityPointWrapper(CUser *self, const int points, const bool b)
{
	self->SetVitalityPoint(points, b);
}

void CUser::SetVitalityPoint(const int points, const bool b)
{
	GUARDED;

	int pointsToSet = points;

	if (Config::Instance()->custom->removeVitalitySystem) {
		pointsToSet = 0;
	}

	reinterpret_cast<void(*)(CUser*, const int, const bool)>(0x89C66C)(this, pointsToSet, b);
}

void CUser::StartOfflineTrade()
{
	GUARDED;

	ScopedLock lock(socket->ext.offlineCS);
	if (socket->ext.offlineUser) {
		return;
	}

	switch (sd->storeMode) {
	case 1:	case 3:	case 5:	case 8: break;
	default:
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"You can use offline store only when trading");
		return;
	}

	CParty *party = GetParty();
	if (party) {
		if (party->GetMaster() == this) {
			party->Dismiss(true);
		} else {
			party->Withdraw(this, true);
		}
	}

	*reinterpret_cast<void**>(socket) = CUserSocket::offlineTradeVtable;

	socket->ext.offlineUser = this;
	socket->IncRef(__FILE__, __LINE__);
	socket->Close();
	socket->user = this;
	socket->ext.offlineSocketHandleCopy = 0;

	acceptPM = false;

	if (Config::Instance()->misc->offlineTradeChangeNameColor) {
		nickColor = 0x7f7f7f;
		ResetNicknameAndColor();
	}

	ext.isOffline = true;

	lock.Release();

	{
		ScopedLock lock(onlineOfflineTradeUsersCS);
		std::set<CUser*>::iterator i = onlineUsers.find(this);
		if (i != onlineUsers.end()) {
			onlineUsers.erase(i);
		}
		offlineTradeUsers.insert(this);
	}
}

void* __cdecl CUser::OfflineTradePartyInvite(void *a, void *b, void *c)
{ GUARDED

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
}

void CUser::SendCharInfo(CUserSocket *socket, const bool b)
{
	GUARDED;

	reinterpret_cast<void(*)(CUser*, CUserSocket*, const bool)>(0x90C3E0)(this, socket, b);

	if (ext.isOffline) {
		switch (sd->storeMode) {
		case 1:	case 3:	case 5:	case 8:
			return;
		default:
			break;
		}

		CUserSocket *socket2 = this->socket;
		if (!socket2) {
			return;
		}

		ScopedLock lock(socket2->ext.offlineCS);
		if (!socket2->ext.offlineUser) {
			return;
		}
		socket2->ext.offlineUser = 0;
		socket2->user = this;
		lock.Release();
		socket2->OnClose();
		socket2->DecRef(__FILE__, __LINE__);
	}
}

void __cdecl CUser::SendUserInfo(CUserSocket *socket)
{
	reinterpret_cast<void(*)(CUser*, CUserSocket*)>(0x909D84)(this, socket);
}

void __cdecl CUser::EnterWorldWrapper(CUser *self)
{
	self->EnterWorld();
}

void CUser::EnterWorld()
{ GUARDED

	{
		ScopedLock lock(onlineOfflineTradeUsersCS);
		onlineUsers.insert(this);
	}
	if (sd->builder) {
		nickColor = 0xff00;
		ResetNicknameAndColor();
		reinterpret_cast<bool(*)(CUserSocket*, CUser*, wchar_t*)>(0x48A8EC)(socket, this, L"//gmon");
	}
	reinterpret_cast<void(*)(CUser*)>(0x8CF0E4)(this);
	if (Config::Instance()->server->protectAfterLoginSeconds > 0) {
		sd->protectAfterLoginExpiry = time(0) + Config::Instance()->server->protectAfterLoginSeconds;
	}
}

void __cdecl CUser::LeaveWorldWrapper(CUser *self)
{
	self->LeaveWorld();
	self->ext.guard.hasEnteredWorld = false;
}

void CUser::LeaveWorld()
{
	GUARDED;

	if (Config::Instance()->server->autoRemoveFromGMList && sd->builder) {
		CUserSocket *socket_ = socket;
		if (socket_) {
			reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x49E898)(socket_, this, L"//gmunreg");
		}
	}
	reinterpret_cast<void(*)(CUser*)>(0x8CB090)(this);
	{
		ScopedLock lock(onlineOfflineTradeUsersCS);
		std::set<CUser*>::iterator i = onlineUsers.find(this);
		if (i != onlineUsers.end()) {
			onlineUsers.erase(i);
		} else {
			std::set<CUser*>::iterator i = offlineTradeUsers.find(this);
			if (i != offlineTradeUsers.end()) {
				offlineTradeUsers.erase(i);
			}
		}
	}
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
{ GUARDED

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
{ GUARDED

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
	GUARDED;

	if (sd && sd->protectAfterLoginExpiry) {
		if (!CSkillInfo::escapeSkills.count(skillId)) {
			sd->protectAfterLoginExpiry = 0;
			if (socket) {
				socket->SendSystemMessage(3108);
			}
		}
	}
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

void __cdecl CUser::FixPendingSkill(CCreature *creature)
{
	GUARDED;

	if (!creature || !creature->IsUser()) {
		return;
	}

	CUser *user = reinterpret_cast<CUser*>(creature);

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
{ GUARDED

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
{ GUARDED
	if (IsNowTrade()) {
		return false;
	}
	return reinterpret_cast<bool(*)(CUser*, UINT32, UINT64)>(0x8E8D54)(this, itemId, itemCount);
}

bool CUser::IsNowTrade() const
{
	return reinterpret_cast<bool(*)(const CUser*)>(0x8A4E8C)(this);
}

void CUser::TradeCancel()
{
	reinterpret_cast<void(*)(CUser*)>(0x8A4C34)(this);
}

bool __cdecl CUser::MultiSellChooseWrapper(CUser *self, int listId, int entryId, UINT64 quantity, int enchant, UINT32 *optionKey, UINT16 *baseAttribute)
{
	return self->MultiSellChoose(listId, entryId, quantity, enchant, optionKey, baseAttribute);
}

bool CUser::MultiSellChoose(int listId, int entryId, UINT64 quantity, int enchant, UINT32 *optionKey, UINT16 *baseAttribute)
{
	GUARDED;

	if (!this) {
		return false;
	}
	if (quantity >= 0xFFFFFFFFll) {
		return false;
	}
	CCreature *target = GetTarget();
	ScopedLock lock(ext.guard.lastMultisellLock);
	if (ext.guard.lastMultisellListId != listId) {
		CLog::Add(CLog::Red, L"User [%s] tried to buy from multisell %d (last = %d)", GetName(), listId,
			ext.guard.lastMultisellListId);
		return false;
	}
	if (Config::Instance()->fixes->multisellFiltering && !ext.guard.allowedMultisellIds.count(listId)) {
		CLog::Add(CLog::Red, L"User [%s] tried to buy from multisell %d (not allowed)", GetName(), listId);
		return false;
	}
	if (!target) {
		return false;
	}
	CSharedCreatureData *sd = target->sd;
	if (!sd || sd->npcClassId != ext.guard.lastMultisellNpcId) {
		return false;
	}
	return reinterpret_cast<bool(*)(CUser*, int, int, UINT64, int, UINT32*, UINT16*)>(
		0x8E9640)(this, listId, entryId, quantity, enchant, optionKey, baseAttribute);
}

void __cdecl CUser::TimerExpiredWrapper(CUser *self, int id)
{
	self->TimerExpired(id);
}

void CUser::TimerExpired(int id)
{
	reinterpret_cast<void(*)(CUser*, int)>(0x8BE4C8)(this, id);
	ProcessPremium();
	if (!cloakSlotUnlocked) {
		if (UnequipItem(SlotTypeBack)) {
			if (socket) {
				socket->SendSystemMessage(2451);
			}
		}
	}
	if (sd->protectAfterLoginExpiry && sd->protectAfterLoginExpiry <= time(0)) {
		sd->protectAfterLoginExpiry = 0;
		if (socket) {
			socket->SendSystemMessage(3108);
		}
	}
}

int __cdecl CUser::GetPremiumLevelWrapper(CUser *self)
{
	return self->GetPremiumLevel();
}

int CUser::GetPremiumLevel()
{
	if (Config::Instance()->custom->ipBasedPremiumSystem) {
		return sd->isPremiumUser ? 1 : 0;
	} else {
		return reinterpret_cast<int(*)(CUser*)>(0x477284)(this);
	}
}

void CUser::ProcessPremium()
{
	CUserSocket *socket = this->socket;
	if (!socket) {
		return;
	}
	bool ipBasedPremiumSystem = Config::Instance()->custom->ipBasedPremiumSystem;
	int ipBasedFixedPCCafePoints = Config::Instance()->custom->ipBasedFixedPCCafePoints;
	if (socket->clientIP.S_un.S_addr && (ipBasedPremiumSystem || ipBasedFixedPCCafePoints >= 0)) {
		bool isPremiumIp = false;
		UINT32 endTime = 0;
		{
			ScopedLock lock(premiumIpAddressesCS);
			std::map<UINT32, UINT32>::const_iterator it = premiumIpAddresses.find(socket->clientIP.S_un.S_addr);
			if (it != premiumIpAddresses.end()) {
				isPremiumIp = true;
				endTime = it->second;
			}
		}
		UINT32 now = time(0);
		if (endTime && endTime < now) {
			isPremiumIp = false;
			endTime = 0;
		}
		if (Config::Instance()->custom->ipBasedPremiumSystem) {
			if (bool(sd->isPremiumUser) != isPremiumIp || ext.premiumEndTime != endTime) {
				sd->isPremiumUser = isPremiumIp;
				ext.premiumEndTime = endTime;
				UINT16 packetId = 0xAA;
				if (Server::GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
					packetId = 0xBC;
				} else if (Server::GetProtocolVersion() == Server::ProtocolVersionGraciaFinalUpdate1) {
					packetId = 0xAB;
				}
				socket->Send("chdc", 0xFE, packetId, objectId, sd->isPremiumUser);
				SendAbnormalStatusInfo();
			}
		}
		if (Config::Instance()->custom->ipBasedFixedPCCafePoints >= 0) {
			int points = 0;
			if (isPremiumIp) {
				points = Config::Instance()->custom->ipBasedFixedPCCafePoints;
			} else if (Config::Instance()->server->fixedPCCafePoints >= 0) {
				points = Config::Instance()->server->fixedPCCafePoints;
			}
			sd->pcPoints = points;
		} else if (Config::Instance()->server->fixedPCCafePoints >= 0) {
			sd->pcPoints = Config::Instance()->server->fixedPCCafePoints;
		}
	} else if (Config::Instance()->server->fixedPCCafePoints >= 0) {
		sd->pcPoints = Config::Instance()->server->fixedPCCafePoints;
	}
}

UINT32 CUser::GetDbId()
{
	return reinterpret_cast<UINT32(*)(CUser*)>(0x407FE8)(this);
}

CSummon* CUser::GetSummonOrPet()
{
	return reinterpret_cast<CSummon*(*)(CUser*)>(0x8FC6CC)(this);
}

bool CUser::AddItemToInventory2(CItem *item)
{
	return reinterpret_cast<bool(*)(CUser*, CItem*)>(0x8D6F98)(this, item);
}

void CUser::SavePoint(int type, int value)
{
	reinterpret_cast<void(*)(CUser*, int, int)>(0x891F90)(this, type, value);
}

void CUser::SendAbnormalStatusInfo()
{
	reinterpret_cast<void(*)(CUser*)>(0x8AF7E4)(this);
}

bool CUser::CanOpenPrivateShopWrapper(CUser *self, int type)
{
	return self->CanOpenPrivateShop(type);
}

bool CUser::CanOpenPrivateShop(int type)
{
	bool result = reinterpret_cast<bool(*)(CUser*, int)>(0x8DADA8)(this, type);
	if (!result) {
		return false;
	}
	double minDistance = Config::Instance()->custom->minShopDistance;
	if (minDistance <= 0) {
		return true;
	}
	switch (sd->storeMode) {
		case 1:	case 3:	case 5:	case 8: return true;
		default: break;
	}
	minDistance *= minDistance;
	{
		ScopedLock lock(onlineOfflineTradeUsersCS);
		for (size_t j = 0 ; j < 2 ; ++j) {
			std::set<CUser*> *list = j ? &offlineTradeUsers : &onlineUsers;
			for (std::set<CUser*>::const_iterator i = list->begin() ; i != list->end() ; ++i) {
				if (*i == this) {
					continue;
				}
				CSharedCreatureData *otherSd = (*i)->sd;
				if (!otherSd) {
					continue;
				}
				switch (otherSd->storeMode) {
					case 1:	case 3:	case 5:	case 8: break;
					default: continue;
				}
				double dx = otherSd->x - sd->x;
				double dy = otherSd->y - sd->y;
				if (dx * dx + dy * dy < minDistance) {
					result = false;
					break;
				}
			}
			if (!result) {
				break;
			}
		}
	}
	if (!result) {
		CUserSocket *s = socket;
		if (s) {
			s->SendSystemMessage(
				Config::Instance()->server->name.c_str(),
				L"You can't open private store here, you must find some empty spot");
		}
	}
	return result;
}

void CUser::SendSkillList(CUserSocket *socket, bool sendShortCutInfo)
{
	reinterpret_cast<void(*)(CUser*, CUserSocket*, bool)>(0x8F6C04)(this, socket, sendShortCutInfo);
}

void CUser::FindAllowedMultisellIds(wchar_t *data)
{
	static const std::wstring multisellBypass = L"action=\"bypass -h menu_select?ask=-303&reply=";
	ScopedLock lock(ext.guard.lastMultisellLock);
	ext.guard.allowedMultisellIds.clear();
	if (data) {
		std::wstring s(data);
		size_t pos = 0;
		for	(;;) {
			if (pos >= s.size()) {
				break;
			}
			pos = s.find(multisellBypass, pos);
			if (pos == std::string::npos) {
				break;
			}
			pos += multisellBypass.size();
			std::wstringstream ss;
			for (;;) {
				if (pos >= s.size()) {
					break;
				} else if (s[pos] >= L'0' && s[pos] <= L'9') {
					ss << s[pos++];
				} else if (s[pos++] == L'"') {
					UINT32 multisellId = 0;
					ss >> multisellId;
					if (ss) {
						ext.guard.allowedMultisellIds.insert(multisellId);
					}
					break;
				} else {
					break;
				}
			}
		}
	}
}

void CUser::ShowHTMLWrapper(CUser *self, wchar_t *filename, wchar_t *data, unsigned int length)
{
	self->ShowHTML(filename, data, length);
}

void CUser::ShowHTML(wchar_t *filename, wchar_t *data, unsigned int i)
{
	FindAllowedMultisellIds(data);
	reinterpret_cast<void(*)(CUser*, wchar_t*, wchar_t*, unsigned int)>(0x8D6594)(this, filename, data, i);
}

void CUser::ShowQuestHTMLWrapper(CUser *self, wchar_t *filename, wchar_t *data, int length)
{
	self->ShowQuestHTML(filename, data, length);
}

void CUser::ShowQuestHTML(wchar_t *filename, wchar_t *data, int i)
{
	FindAllowedMultisellIds(data);
	reinterpret_cast<void(*)(CUser*, wchar_t*, wchar_t*, int)>(0x8D61C8)(this, filename, data, i);
}

bool __cdecl CUser::IsValidPrivateStoreItemWrapper(CUser *self, INT64 count, INT64 price, CItem *item)
{
	return self->IsValidPrivateStoreItem(count, price, item);
}

bool CUser::IsValidPrivateStoreItem(INT64 count, INT64 price, CItem *item)
{
	if (!reinterpret_cast<bool(*)(CUser*, INT64, INT64, CItem*)>(0x88D740)(this, count, price, item)) {
		return false;
	}
	if (item->sd->ext.isPrivateStoreSet) {
		if (!item->sd->ext.isPrivateStore) {
			return false;
		}
	} else {
		if (!item->IsTradeable(this)) {
			return false;
		}
	}
	if (!item->worldInfo || item->worldInfo->consumeType != 2) {
		return true;
	}
	if (GetItemCount(item->itemId) != item->worldInfo->count) {
		CLog::Add(CLog::Red, L"User [%s] trying to put multiple item [%d] stacks into private store",
			GetName(), item->itemId);
		return false;
	}
	return true;
}

void __cdecl CUser::OutOfSightWrapper(CUser *self, CObject *object, bool b)
{
	self->OutOfSight(object, b);
}

void CUser::OutOfSight(CObject *object, bool b)
{
	GUARDED;

	if (IsUser()) {
		CCreature *creature = reinterpret_cast<CCreature*>(object);
		if (creature->IsValidCreature()) {
			if (targetId == creature->objectId) {
				ChangeTarget(0, 2);
			}
			void *action = GetVfn<void*(*)(void*)>(creatureController, 0xA)(creatureController);
			if (action) {
				if (GetVt(action) == 0xADFCC8) {
					CAttackAction *attackAction = reinterpret_cast<CAttackAction*>(action);
					if (attackAction->targetId == creature->objectId) {
						DoNothing();
					}
				} else if (GetVt(action) == 0xB91F48) {
					CSkillAction2 *skillAction = reinterpret_cast<CSkillAction2*>(action);
					if (skillAction->targetId == creature->objectId) {
						DoNothing();
					}
				}
			}
		}
	}
	GetVfn<void(*)(CCreature*, CObject*, bool)>(this, 0x82)(this, object, b);
}

void __cdecl CUser::SetPointWrapper(CUser *self, int type, int value)
{
	if (type == 5) {
		ScopedLock lock(self->ext.cs);
		if (!self->ext.famePointLoaded) {
			CLog::Add(CLog::Red,
				L"User [%s]: can't set fame points: not loaded yet (requesting load again)",
				self->sd->name);
			CDB::Instance()->RequestLoadUserPoint(self, 5);
			return;
		}
	}
	reinterpret_cast<void(*)(CUser*, int, int)>(0x891CF0)(self, type, value);
}

void __cdecl CUser::AddPointWrapper(CUser *self, int type, int value, bool b)
{
	if (type == 5) {
		ScopedLock lock(self->ext.cs);
		if (!self->ext.famePointLoaded) {
			CLog::Add(CLog::Red,
				L"User [%s]: can't add fame points: not loaded yet (requesting load again)",
				self->sd->name);
			CDB::Instance()->RequestLoadUserPoint(self, 5);
			return;
		}
	}
	reinterpret_cast<void(*)(CUser*, int, int, bool)>(0x89CBC4)(self, type, value, b);
}

void __cdecl CUser::SetPointWrapperOnLoad(CUser *self, int type, int value)
{
	reinterpret_cast<void(*)(CUser*, int, int)>(0x891CF0)(self, type, value);
	if (self && type == 5) {
		ScopedLock lock(self->ext.cs);
		self->ext.famePointLoaded = true;
	}
}

void __cdecl CUser::SetMessage_dWrapper(void *self, int line, const wchar_t *format, int value)
{
	if (line > 4) {
		++line;
	}

	reinterpret_cast<void(*)(void*, int, const wchar_t*, int)>(0x8624D4)(
		self, line, format, value);

	if (line == 4) {
		{
			ScopedLock lock(onlineOfflineTradeUsersCS);
			value = offlineTradeUsers.size();
		}
		reinterpret_cast<void(*)(void*, int, const wchar_t*, int)>(0x8624D4)(
			self, line + 1, L"User(n) Offline trade: %d", value);
	}
}

void __cdecl CUser::SetMessageVWrapper(void *self, int line, const wchar_t *format, ...)
{
	if (line > 4) {
		++line;
	}
	reinterpret_cast<void(*)(void*, int, const wchar_t*, ...)>(0x86258C)(self, line, format);
}

void __cdecl CUser::GetObjectTradeFix(void*, SmartPtr<CCreature> *ptr, UINT32 objectId)
{
	CCreature *creature = ptr->GetObject(objectId);
	if (!creature->IsUser()) return;
	CUser *user = reinterpret_cast<CUser*>(creature);
	if (Guard::WasCalled(reinterpret_cast<wchar_t*>(0xC36040))) return; // "bool __cdecl CTrade::Canceled(class User *)"
	if (!user->IsNowTrade()) return;
	if (Guard::WasCalled(reinterpret_cast<wchar_t*>(0xB143A0))) return; // "bool __cdecl DBPacketHandler::ReplyTrade(class CDBSocket *,const unsigned char *)"
	if (Guard::WasCalled(reinterpret_cast<wchar_t*>(0xB16E20))) return; // "bool __cdecl ManipulateItemPacket(class CDBSocket *,const unsigned char *)>"
	if (Guard::WasCalled(reinterpret_cast<wchar_t*>(0xC36140))) return; // "int __cdecl CTrade::AddItems(const unsigned char *,unsigned int)"
	if (Guard::WasCalled(reinterpret_cast<wchar_t*>(0xC5A500))) return; // "void __cdecl User::DecreaseEquippedItemDurationOnTimerExpired(void)"
	user->TradeCancel();
}

void CUser::SetDailyQuest(UINT32 questId)
{
	time_t now = time(0);
	for (size_t i = 0 ; i < 25 ; ++i) {
		if (!sd->dailyQuests[i].questId || sd->dailyQuests[i].questId == questId) {
			sd->dailyQuests[i].questId = questId;
			sd->dailyQuests[i].completeTime = now;
			CDB::Instance()->SetDailyQuest(GetServerId(), questId, now);
			return;
		}
	}
	CLog::Add(CLog::Red, L"Warning: no empty daily quest slot for user [%s], quest = %d, time = %d",
		GetName(), questId, now);
}

bool CUser::ReplyEnchantItem(CItem *scroll, INT64 scrollNewCount,
							 CItem *catalyst, INT64 catalystNewCount,
							 CItem *enchantedItem, int newEnchantValue)
{
	bool ret = reinterpret_cast<bool(*)(CUser*, CItem*, INT64, CItem*, INT64, CItem*, int)>(0x8E55C0)(
		this, scroll, scrollNewCount, catalyst, catalystNewCount, enchantedItem, newEnchantValue);

	if (!Config::Instance()->server->epilogueEnchantFirecracker) {
		return ret;
	}

	bool firecracker = false;
	if (enchantedItem) {
		if (enchantedItem->worldInfo->itemType == 0) {
			if (newEnchantValue == 7 || newEnchantValue == 15) {
				firecracker = true;
			}
		} else if(enchantedItem->worldInfo->itemType == 1) {
			if (newEnchantValue == 6) {
				firecracker = true;
			}
		}
	}

	if (firecracker) {
		BroadcastSkillUse(2024, 1); // firecracker
		reinterpret_cast<void(*)(UINT64, CCreature*, int, double*, int, const char*, ...)>(0x421EC8)(
			0x10FF64D8, this, 0x5000, GetPosition(), 0x5DC,
			"cdddSdddd", 0x62, 3013, 3, 0, GetName(), 1, newEnchantValue, 3, enchantedItem->itemId);
	}

	return ret;
}

int CUser::CVitalityPointGetDecrementValue(int level)
{
	if (Config::Instance()->server->epilogueVitalitySystem && level > 75) {
		level = 75;
	}
	return reinterpret_cast<int(*)(int)>(0x9593EC)(level);
}

CompileTimeOffsetCheck(CUser, acceptPM, 0x35D8);
CompileTimeOffsetCheck(CUser, padding0x35D9, 0x35D9);
CompileTimeOffsetCheck(CUser, isVitalityReplenishing, 0x38B0);
CompileTimeOffsetCheck(CUser, ext, 0x3A10);

