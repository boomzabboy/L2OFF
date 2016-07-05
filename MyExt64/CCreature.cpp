
#include "CCreature.h"
#include "CSharedCreatureData.h"
#include "CYieldLock.h"
#include "Utils.h"

int CCreature::GetAcquiredSkillLevel(int skillId)
{
	typedef int (__thiscall *t)(CCreature*, int);
	t f = reinterpret_cast<t>(0x5502D8);
	return f(this, skillId);
}

int CCreature::GetLevel()
{
	return sd->level;
}

wchar_t* CCreature::GetName()
{
	return sd->name;
}

bool CCreature::IsBoss() const
{
	return reinterpret_cast<const UINT64*>(this)[0] == 0xA72FB8;
}

CompileTimeOffsetCheck(CCreature, sdLock, 0x0AA0);

