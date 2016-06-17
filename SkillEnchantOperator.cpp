
#include "SkillEnchantOperator.h"
#include "CSkillEnchantInfo.h"

SkillEnchantOperator* __cdecl SkillEnchantOperator::GetOperator(UINT32 type)
{
	typedef void* (__cdecl *t1)();
	t1 f1 = reinterpret_cast<t1>(0x472C08);
	typedef SkillEnchantOperator* (__cdecl *t2)(void*, UINT32&);
	t2 f2 = reinterpret_cast<t2>(0x44BD0C);
	return f2(f1(), type);
}

int SkillEnchantOperator::CalculateProb(CSkillEnchantInfo *info, int level)
{
	typedef int (__thiscall *t)(SkillEnchantOperator*, CSkillEnchantInfo*, int);
	t f = reinterpret_cast<t>(
		*reinterpret_cast<void**>(
			reinterpret_cast<unsigned char*>(vtable) + 0x38));
	return f(this, info, level);
}

