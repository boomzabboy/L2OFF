
#include "CUser.h"

int CUser::GetAcquiredSkillLevel(int skillId)
{
	typedef int (__thiscall *t)(CUser*, int);
	t f = reinterpret_cast<t>(0x5502D8);
	return f(this, skillId);
}

int CUser::GetLevel()
{
	return sd->level;
}

wchar_t* CUser::GetName()
{
	return sd->name;
}

