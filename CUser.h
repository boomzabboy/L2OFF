
#pragma once

#include <windows.h>
#include "CriticalSection.h"
#include <string>

class CUser {
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

	int GetAcquiredSkillLevel(int skillId);
	int GetLevel();
	wchar_t* GetName();
	UINT64 GetItemCount(UINT32 itemId);
	void TakeItem(UINT32 itemId, UINT64 count);
	void Say(const wchar_t *message);
	void StartOfflineTrade();
	INT64 ExpInc(const INT64 exp, const bool b);
	void AddVitalityPoint(const int points, const int type, const bool b);

	static void __cdecl SayWrapper(CUser *self, const wchar_t *message);
	static INT64 __cdecl ExpIncWrapper(CUser *self, const INT64 exp, const bool b);
	static void __cdecl AddVitalityPointWrapper(CUser *self, const int points, const int type, const bool b);

	static CriticalSection counterCS;
	static size_t counterTotal;
	static size_t counterOffline;

	/* 0x0000 */ unsigned char padding0x0000[0x18];
	/* 0x0018 */ UINT32 objectId;
	/* 0x001C */ unsigned char padding0x001C[0xA74];
	/* 0x0A90 */ class CSharedCreatureData *sd;
	/* 0x0A98 */ unsigned char padding0x0A98[0x8];
	/* 0x0AA0 */ class CYieldLock *sdLock;
	/* 0x0AA8 */ unsigned char padding0xAA8[0x17A0];
	/* 0x2248 */ void *economy;
	/* 0x2250 */ unsigned char padding0x2250[0x1108];
	/* 0x3358 */ class CUserSocket *socket;
	/* 0x3360 */ unsigned char padding0x3360[0x550];
	/* 0x38B0 */ unsigned int isVitalityReplenishing;
	/* 0x38B4 */ unsigned char padding0x38B4[0x15C];

	/* EXT DATA BEGIN AT 0x3A10 */
	/* 0x3A10 */ Ext ext;

};

