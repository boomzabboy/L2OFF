
#pragma once

#include <windows.h>
#include <vector>

class CSkillInfo {
public:
	static void Init();

	class Ext {
	public:
		Ext();
		~Ext();

		bool olympiadUse;
	};

	CSkillInfo* Constructor();
	void Destructor(bool isMemoryFreeUsed);

	static bool __cdecl IsValidTargetWrapper(CSkillInfo *self, class CCreature *attacker, class CCreature *target, bool b);

	bool IsValidTarget(class CCreature *attacker, class CCreature *target, bool b);
	void ActivateSkill(class CCreature *caster, class CObject *target, double unknown1, void *unknown2, int unknown3, double unknown4);
	bool PushCondition(class CSkillOperateCondition *condition, const int operateConditionTarget);
	bool CanUsedBy(class CCreature *caster, bool b) const;

	/* 0x0000 */ unsigned char padding0x0000[0x0010 - 0x0000];
	/* 0x0010 */ UINT32 skillId;
	/* 0x0014 */ UINT32 level;
	/* 0x0018 */ unsigned char padding0x0018[0x0194 - 0x0018];
	/* 0x0194 */ UINT32 abnormalVisualEffect;
	/* 0x0198 */ UINT32 abnormalVisualEffect2;
	/* 0x019C */ unsigned char padding0x019C[0x0218 - 0x019C];
	/* 0x0218 */ std::vector<void*> effects[7];
	/* 0x02F8 */ unsigned char padding0x02F8[0x0394 - 0x02F8];
	/* 0x0394 */ UINT32 abnormalVisualEffect3;
	/* 0x0398 */ CSkillInfo::Ext ext;
};

