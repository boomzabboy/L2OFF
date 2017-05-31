
#pragma once

#include <Server/CObject.h>
#include <Server/CInventory.h>
#include <windows.h>

class CCreature : public CObject {
protected:
	CCreature();
	~CCreature();

public:
	static void Init();

	int GetAcquiredSkillLevel(int skillId);
	int GetLevel();
	wchar_t* GetName();
	bool IsBoss() const;
	bool IsUser() const;
	bool IsSummon() const;
	bool IsPet() const;
	bool IsUserOrSummon() const;
	bool AddItemToInventory(int itemId, UINT64 count);
	CCreature* GetTarget();
	unsigned long GetSkillUsedTime(const int skillId);
	int GetRemainReuseDelaySec(const int skillId);
	bool UseItem(class CItem *item, int i);
	bool IsValidCreature() const;
	void DoNothing();
	void ChangeTarget(CObject *target, int reason);
	void UnequipWeapon();
	bool UnequipItem(enum SlotType slotType);
	UINT32 GetServerId();
	bool IsEnemyTo(CCreature *creature);
	void BroadcastSkillUse(const int skillId, const int skillLevel, const int hitTime = 200, const int reuseTime = 200);

	static CCreature* GetCreatureByObjectId(UINT32 id);
	static CCreature* GetValidCreatureByObjectId(UINT32 id);

	static int __cdecl GetRemainReuseDelaySecWrapper(CCreature *self, const int skillId);
	static bool __cdecl UseItemWrapper(CCreature *self, class CItem *item, int i);
	static CCreature* __cdecl GetUserOrMaster(CCreature *self);
	static void __cdecl UnequipWeaponWrapper(CCreature *self);

	/* 0x0000 */ unsigned char padding0x0000[0x0018 - 0x0000];
	/* 0x0018 */ UINT32 objectId;
	/* 0x001C */ UINT32 objectType;
	/* 0x0020 */ unsigned char padding0x001C[0x0A90 - 0x0020];
	/* 0x0A90 */ class CSharedCreatureData *sd;
	/* 0x0A98 */ unsigned char padding0x0A98[0x0AA0 - 0x0A98];
	/* 0x0AA0 */ class CYieldLock *sdLock;
	/* 0x0AA8 */ CInventory inventory;
	/* 0x0B78 */ unsigned char padding0x0B78[0x11E8 - 0x0B78];
	/* 0x11E8 */ bool cloakSlotUnlocked;
	/* 0x11E9 */ unsigned char padding0x11E9[0x1210 - 0x11E9];
	/* 0x1210 */ bool hide;
	/* 0x1211 */ unsigned char padding0x1211[0x1460 - 0x1211];
	/* 0x1460 */ UINT32 targetId;
	/* 0x1464 */ unsigned char padding0x1464[0x1468 - 0x1464];
	/* 0x1468 */ void *creatureController;
	/* 0x1470 */ unsigned char padding0x1470[0x1CB0 - 0x1470];
	/* 0x1CB0 */
};

