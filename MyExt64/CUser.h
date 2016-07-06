
#pragma once

#include <windows.h>
#include "CCreature.h"
#include "CriticalSection.h"
#include <string>

class CUser : public CCreature {
public:
	static void Init();

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
			int storedReply;
			bool firstBuySell;
			bool fakeSell;
			BuySellList sellList;
			BuySellList buyList;
			bool buySellSwitched;
		};

		BuySell buySell;
		bool isExpOff;
		bool isOffline;
	};

	UINT64 GetItemCount(UINT32 itemId);
	void TakeItem(UINT32 itemId, UINT64 count);
	void Say(const wchar_t *message);
	void StartOfflineTrade();
	INT64 ExpInc(const INT64 exp, const bool b);
	void AddVitalityPoint(const int points, const int type, const bool b);
	class CParty* GetParty();
	void ResetNicknameAndColor();
	void SendCharInfo(class CUserSocket *socket, const bool b);
	void EnterWorld();
	class CMultiPartyCommandChannel* GetMPCC();
	void SendRelationChanged(class CUserSocket *socket);
	bool IsEnemyTo(CCreature *creature);
	int GetRelationTo(CUser *user);

	static void __cdecl SayWrapper(CUser *self, const wchar_t *message);
	static INT64 __cdecl ExpIncWrapper(CUser *self, const INT64 exp, const bool b);
	static void __cdecl AddVitalityPointWrapper(CUser *self, const int points, const int type, const bool b);
	static void* __cdecl OfflineTradePartyInvite(void *a, void *b, void *c);
	static void __cdecl SendCharInfoWrapper(CUser *self, class CUserSocket *socket, const bool b);
	static void __cdecl EnterWorldWrapper(CUser *self);
	static bool __cdecl IsEnemyToWrapper(CUser *self, CCreature *creature);
	static int __cdecl GetRelationToWrapper(CUser *self, CUser *user);

	static CriticalSection counterCS;
	static size_t counterTotal;
	static size_t counterOffline;

	/* 0x1CB0 */ unsigned char padding0x1CB0[0x598];
	/* 0x2248 */ void *economy;
	/* 0x2250 */ unsigned char padding0x2250[0x1108];
	/* 0x3358 */ class CUserSocket *socket;
	/* 0x3360 */ unsigned char padding0x3360[0x278];
	/* 0x35D8 */ bool acceptPM;
	/* 0x35D9 */ unsigned char padding0x35D9[0x19F];
	/* 0x3778 */ UINT32 nickColor;
	/* 0x377C */ unsigned char padding0x377C[0x134];
	/* 0x38B0 */ unsigned int isVitalityReplenishing;
	/* 0x38B4 */ unsigned char padding0x38B4[0x15C];

	/* EXT DATA BEGIN AT 0x3A10 */
	/* 0x3A10 */ Ext ext;
};

