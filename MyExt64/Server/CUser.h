
#pragma once

#include <windows.h>
#include <Server/CCreature.h>
#include <Server/CShortCut.h>
#include <Common/CriticalSection.h>
#include <Common/CYieldLock.h>
#include <string>
#include <set>
#include <map>

class CUser : public CCreature {
protected:
	CUser();
	~CUser();

public:
	struct InZoneRestriction {
		int time;
		int cnt;
		int unknown;
	};

	static void Init();
	static DWORD PremiumIpRefresh(void *v);

	static CUser* __cdecl Constructor(CUser *self, wchar_t* characterName, wchar_t* accountName,
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
									  unsigned int uUnk19, unsigned int uUnk20, unsigned int uUnk21, unsigned int uUnk22, bool bUnk23);
	static CUser* __cdecl Destructor(CUser *self, bool isMemoryFreeUsed);

	class Ext {
	public:
		Ext();
		~Ext();

		class BuySell {
		public:
			class BuySellList {
			public:
				BuySellList();

				UINT64 adena;
				UINT32 id;
				UINT32 itemCount;
				std::string items;
			};

			BuySell();

			void *economy2;
			UINT32 storedNpcSdIndex;
			int storedAsk;
			int storedReply;
			int storedState;
			bool firstBuySell;
			bool fakeSell;
			BuySellList sellList;
			BuySellList buyList;
			bool buySellSwitched;
		};

		class LastSkill {
		public:
			LastSkill();

			int skillId;
			UINT32 firstFail;
			bool ctrl;
			bool shift;
		};

		class Guard {
		public:
			Guard();

			UINT32 lastDropItem;
			UINT32 lastChangeItem;
			bool isEnchanting;
			bool hasEnteredWorld;
			CriticalSection lastMultisellLock;
			UINT32 lastMultisellNpcId;
			UINT32 lastMultisellListId;
			std::set<UINT32> allowedMultisellIds;
		};

		BuySell buySell;
		bool isExpOff;
		bool isOffline;
		LastSkill lastSkill;
		Guard guard;
		bool autoloot;
		UINT32 premiumEndTime;
	};

	UINT64 GetItemCount(UINT32 itemId);
	bool TakeItem(UINT32 itemId, UINT64 count);
	void Say(const wchar_t *message);
	void StartOfflineTrade();
	INT64 ExpInc(const INT64 exp, const bool b);
	void AddVitalityPoint(const int points, const int type, const bool b);
	void SetVitalityPoint(const int points, const bool b);
	class CParty* GetParty();
	void ResetNicknameAndColor();
	void SendCharInfo(class CUserSocket *socket, const bool b);
	void SendUserInfo(class CUserSocket *socket = 0);
	void EnterWorld();
	void LeaveWorld();
	class CMultiPartyCommandChannel* GetMPCC();
	void SendRelationChanged(class CUserSocket *socket);
	bool IsEnemyTo(CCreature *creature);
	int GetRelationTo(CUser *user);
	bool OnMagicSkillUsePacket(int skillId, bool ctrl, bool shift);
	bool OnMagicSkillUsePacketOriginal(int skillId, bool ctrl, bool shift);
	bool IsInBlockList(int id);
	bool IsInBlockListOriginal(int id);
	bool IsWaitingForOlympiad() const;
	bool IsInOlympiad() const;
	bool DeleteItemInInventoryBeforeCommit(const UINT32 itemId, const UINT64 itemCount);
	bool IsNowTrade() const;
	void TradeCancel();
	bool MultiSellChoose(int listId, int entryId, UINT64 quantity, int enchant, UINT32 *optionKey, UINT16 *baseAttribute);
	UINT32 GetDbId();
	class CSummon* GetSummonOrPet();
	bool AddItemToInventory2(class CItem *item);
	void SavePoint(int type, int value);
	void TimerExpired(int id);
	int GetPremiumLevel();
	void ProcessPremium();
	void SendAbnormalStatusInfo();
	bool CanOpenPrivateShop(int type);
	void SendSkillList(class CUserSocket *socket, bool sendShortCutInfo);
	void FindAllowedMultisellIds(wchar_t *data);
	void ShowHTML(wchar_t *filename, wchar_t *data, unsigned int i);
	void ShowQuestHTML(wchar_t *filename, wchar_t *data, int i);
	bool IsValidPrivateStoreItem(INT64 count, INT64 price, class CItem *item);
	void OutOfSight(CObject *object, bool b);

	static void __cdecl SayWrapper(CUser *self, const wchar_t *message);
	static INT64 __cdecl ExpIncWrapper(CUser *self, const INT64 exp, const bool b);
	static void __cdecl AddVitalityPointWrapper(CUser *self, const int points, const int type, const bool b);
	static void __cdecl SetVitalityPointWrapper(CUser *self, const int point, const bool b);
	static void* __cdecl OfflineTradePartyInvite(void *a, void *b, void *c);
	static void __cdecl SendCharInfoWrapper(CUser *self, class CUserSocket *socket, const bool b);
	static void __cdecl EnterWorldWrapper(CUser *self);
	static void __cdecl LeaveWorldWrapper(CUser *self);
	static bool __cdecl IsEnemyToWrapper(CUser *self, CCreature *creature);
	static int __cdecl GetRelationToWrapper(CUser *self, CUser *user);
	static bool __cdecl OnMagicSkillUsePacketWrapper(CUser *self, int skillId, bool ctrl, bool shift);
	static void __cdecl FixPendingSkill(CCreature *creature);
	static bool __cdecl IsInBlockListWrapper(CUser *self, int id);
	static bool __cdecl DeleteItemInInventoryBeforeCommitWrapper(CUser *self, const UINT32 itemId, const UINT64 itemCount);
	static bool __cdecl MultiSellChooseWrapper(CUser *self, int listId, int entryId, UINT64 quantity, int enchant, UINT32 *optionKey, UINT16 *baseAttribute);
	static void __cdecl TimerExpiredWrapper(CUser *self, int id);
	static int __cdecl GetPremiumLevelWrapper(CUser *self);
	static bool __cdecl CanOpenPrivateShopWrapper(CUser *self, int type);
	static void __cdecl ShowHTMLWrapper(CUser *self, wchar_t *filename, wchar_t *data, unsigned int i);
	static void __cdecl ShowQuestHTMLWrapper(CUser *self, wchar_t *filename, wchar_t *data, int i);
	static bool __cdecl IsValidPrivateStoreItemWrapper(CUser *self, INT64 count, INT64 price, class CItem *item);
	static void __cdecl OutOfSightWrapper(CUser *self, CObject *object, bool b);

	static CriticalSection onlineOfflineTradeUsersCS;
	static std::set<CUser*> onlineUsers;
	static std::set<CUser*> offlineTradeUsers;
	static CriticalSection premiumIpAddressesCS;
	static std::map<UINT32, UINT32> premiumIpAddresses;

	/* 0x1CB0 */ unsigned char padding0x1CB0[0x2248 - 0x1CB0];
	/* 0x2248 */ void *economy;
	/* 0x2250 */ unsigned char padding0x2250[0x22DA - 0x2250];
	/* 0x22DA */ bool spiritshotOn;
	/* 0x22DB */ unsigned char padding0x22DB[0x2428 - 0x22DB];
	/* 0x2428 */ CShortCut shortCut;
	/* 0x3210 */ unsigned char padding0x3210[0x3264 - 0x3210];
	/* 0x3264 */ CYieldLock htmlLock;
	/* 0x3270 */ unsigned char padding0x3270[0x3298 - 0x3270];
	/* 0x3298 */ unsigned int olympiadStatus;
	/* 0x329C */ unsigned char padding0x329C[0x3358 - 0x329C];
	/* 0x3358 */ class CUserSocket *socket;
	/* 0x3360 */ UINT32 tradeId;
	/* 0x3364 */ unsigned char padding0x3360[0x35D8 - 0x3364];
	/* 0x35D8 */ bool acceptPM;
	/* 0x35D9 */ unsigned char padding0x35D9[0x3778 - 0x35D9];
	/* 0x3778 */ UINT32 nickColor;
	/* 0x377C */ unsigned char padding0x377C[0x3818 - 0x377C];
	/* 0x3818 */ std::map<UINT32, InZoneRestriction> inZoneRestrictionMap1;
	/* 0x3830 */ std::map<UINT32, InZoneRestriction> inZoneRestrictionMap2;
	/* 0x3848 */ unsigned char padding0x3848[0x38B0 - 0x3848];
	/* 0x38B0 */ unsigned int isVitalityReplenishing;
	/* 0x38B4 */ unsigned char padding0x38B4[0x3A10 - 0x38B4];

	/* EXT DATA BEGIN AT 0x3A10 */
	/* 0x3A10 */ Ext ext;
};

