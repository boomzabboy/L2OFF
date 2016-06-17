
#pragma once

class CSkillEnchantDB {
public:
	static CSkillEnchantDB* GetInstance();
	class CSkillEnchantInfo* GetSkillEnchantInfo(int skillId, int skillLevel);
};

