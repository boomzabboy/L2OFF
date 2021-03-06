
#include <Server/CSkillEnchantDB.h>
#include <Server/CSkillEnchantInfo.h>
#include <Common/Utils.h>

CSkillEnchantDB* CSkillEnchantDB::GetInstance()
{
	return reinterpret_cast<CSkillEnchantDB*>(0x10F6A7B0);
}

CSkillEnchantInfo* CSkillEnchantDB::GetSkillEnchantInfo(int skillId, int skillLevel)
{ GUARDED

	typedef CSkillEnchantInfo* (__thiscall *t)(CSkillEnchantDB*, int, int);
	t f = reinterpret_cast<t>(0x826EDC);
	return f(this, skillId, skillLevel);
}

