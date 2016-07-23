
#pragma once

#include <Server/CObject.h>
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
	bool AddItemToInventory(int itemId, UINT64 count);
	CCreature* GetTarget();
	unsigned long GetSkillUsedTime(const int skillId);
	int GetRemainReuseDelaySec(const int skillId);

	static int __cdecl GetRemainReuseDelaySecWrapper(CCreature *self, const int skillId);

	/* 0x0000 */ unsigned char padding0x0000[0x18];
	/* 0x0018 */ UINT32 objectId;
	/* 0x001C */ unsigned char padding0x001C[0xA74];
	/* 0x0A90 */ class CSharedCreatureData *sd;
	/* 0x0A98 */ unsigned char padding0x0A98[0x8];
	/* 0x0AA0 */ class CYieldLock *sdLock;
	/* 0x0AA8 */ unsigned char padding0x0AA8[0x9B8];
	/* 0x1460 */ UINT32 targetId;
	/* 0x1464 */ unsigned char padding0x1464[0x84C];
	/* 0x1CB0 */
};

