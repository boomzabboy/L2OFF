
#pragma once

#include <windows.h>
#include <vector>
#include <set>

class CSkillInfo {
public:
	static void Init();

	class Ext {
	public:
		Ext();
		~Ext();

		bool olympiadUse;
	};

	enum TargetType {
		self = 0,
		target = 1,
		others = 2,
		enemy = 4,
		enemy_only = 5,
		item = 6,
		summon = 7,
		holything = 8,
		door_treasure = 10,
		pc_body = 11,
		npc_body = 12,
		wyvern_target = 13,
		ground = 14,
		artillery = 15,
		fortress_flagpole = 16,
		advance_base = 18,
		enemy_not = 19,
		end
	};

	CSkillInfo* Constructor();
	void Destructor(bool isMemoryFreeUsed);

	static class CSkillOperateCondition *lastAddedCondition;
	static std::set<int> escapeSkills;

	static bool __cdecl IsValidTargetWrapper(CSkillInfo *self, class CCreature *attacker, class CCreature *target, bool b);
	static UINT64 IsValidTargetHelper(UINT32 targetType);

	bool IsValidTarget(class CCreature *attacker, class CCreature *target, bool b);
	void ActivateSkill(class CCreature *caster, class CObject *target, double unknown1, void *unknown2, int unknown3, double unknown4);
	bool PushCondition(class CSkillOperateCondition *condition, const int operateConditionTarget);
	bool CanUsedBy(class CCreature *caster, bool b) const;

	/* 0x0000 */ unsigned char padding0x0000[0x0008 - 0x0000];
	/* 0x0008 */ wchar_t *skillName;
	/* 0x0010 */ UINT32 skillId;
	/* 0x0014 */ UINT32 level;
	/* 0x0018 */ unsigned char padding0x0018[0x0194 - 0x0018];
	/* 0x0194 */ UINT32 abnormalVisualEffect;
	/* 0x0198 */ UINT32 abnormalVisualEffect2;
	/* 0x019C */ unsigned char padding0x019C[0x0218 - 0x019C];
	/* 0x0218 */ std::vector<void*> effects[7];
	/* 0x02F8 */ unsigned char padding0x02F8[0x0340 - 0x02F8];
	/* 0x0340 */ UINT32 targetType;
	/* 0x0344 */ unsigned char padding0x0344[0x0394 - 0x0344];
	/* 0x0394 */ UINT32 abnormalVisualEffect3;
	/* 0x0398 */ CSkillInfo::Ext ext;
};

