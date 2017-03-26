
#pragma once

#include <windows.h>

class CSharedCreatureData {
public:
	static void InitNpc();
	static void InitServer();

	/* 0x0000 */ unsigned char padding0x0000[0x8];
	/* 0x0008 */ double x;
	/* 0x0010 */ double y;
	/* 0x0018 */ double z;
	/* 0x0020 */ INT32 heading;
	/* 0x0024 */ UINT32 objectId;
	/* 0x0028 */ UINT32 index;
	/* 0x002C */ unsigned char padding0x002C[0x0068-0x002C];
	/* 0x0068 */ INT32 isAlive;
	/* 0x006C */ unsigned char padding0x006C[0x007C-0x006C];
	/* 0x007C */ UINT32 noblesseType;
	/* 0x0080 */ unsigned char padding0x0080[0x0098-0x0080];
	/* 0x0098 */ INT32 race;
	/* 0x009C */ INT32 class_;
	/* 0x00A0 */ INT32 sex;
	/* 0x00A4 */ WCHAR name[25];
	/* 0x00D6 */ unsigned char padding0x00D6[0x0100-0x00D6];
	/* 0x0100 */ UINT64 exp;
	/* 0x0108 */ UINT32 sp;
	/* 0x010C */ unsigned char padding0x010C[0x06AC-0x010C];
	/* 0x06AC */ INT32 storeMode;
	/* 0x06B0 */ unsigned char padding0x06B0[0x07A4-0x06B0];
	/* 0x07A4 */ UINT32 level;
	/* 0x07A8 */ unsigned char padding0x07A8[0x08C8-0x07A8];
	/* 0x08C8 */ UINT32 builder;
	/* 0x08CC */ unsigned char padding0x08CC[0x0930-0x08CC];
	/* 0x0930 */ UINT32 isInsidePeaceZone;
	/* 0x0934 */ unsigned char padding0x0934[0x0938-0x0934];
	/* 0x0938 */ UINT32 pcPoints;
	/* 0x093C */ unsigned char padding0x093C;
	/* 0x093D */ unsigned char isPremiumUser;
	/* 0x093E */ unsigned char padding0x093E[0x0A5C-0x093E];
	/* 0x0A5C */ UINT32 summonTime;
	/* 0x0A60 */ UINT32 maxTime;
	/* 0x0A64 */ unsigned char padding0x0A64[0x0A7C-0x0A64];
	/* 0x0A7C */ UINT32 npcClassId;
	/* 0x0A80 */ unsigned char padding0x0A80[0x0B10-0x0A80];
	/* 0x0B10 */ UINT32 food;
	/* 0x0B14 */ UINT32 foodMax;
	/* 0x0B18 */ unsigned char padding0x0B18[0x0B30-0x0B18];
	/* 0x0B30 */ UINT32 inZoneId;
	/* 0x0B34 */ unsigned char padding0x0B34[0x0DF8-0x0B34];
	/* 0x0DF8 */ unsigned char padding0x0DF8[0x1378-0x0DF8];
	/* 0x1378 */ UINT32 absolute_defence;
	/* 0x137C */ UINT32 no_attack_damage;
	/* 0x1380 */ unsigned char padding0x1380[0x15C0-0x1380];
	/* 0x15C0 */ UINT32 quest_inv_items;
	/* 0x15C4 */ unsigned char padding0x15C4[0x16E4-0x15C4];
	/* 0x16E4 */ UINT32 m_nPvP_Event_Kills;
	/* 0x16E8 */ UINT32 m_nPvP_Event_Deaths;
	/* 0x16EC */ UINT32 m_nPvP_Event_EventId;
	/* 0x16F0 */ UINT32 m_nPvP_Event_TeamId;
	/* 0x16F4 */ UINT32 m_nPvP_Event_KillsSequenced;
	/* 0x16F8 */ UINT32 m_nPvP_Event_MemberId;
	/* 0x16FC */ UINT32 m_nMultiBoxSessionCount;
	/* 0x1700 */ wchar_t wedding_partner_name[26];
	/* 0x1734 */ UINT32 wedding_relation;
};

