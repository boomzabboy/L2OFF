
#include "CUser.h"
#include "CSharedCreatureData.h"
#include "Utils.h"
#include <new>

void CUser::Init()
{
	WriteMemoryDWORD(0x5AEF0E, sizeof(CUser));
	WriteMemoryDWORD(0x5E1869, sizeof(CUser));
	WriteInstruction(0x5E1ACA, reinterpret_cast<UINT32>(Constructor), 0xE8);
	WriteInstruction(0x8D4340, reinterpret_cast<UINT32>(Destructor), 0xE8);
}

CUser* __cdecl CUser::Constructor(CUser *self, wchar_t* characterName, wchar_t* accountName,
								  unsigned int characterId, unsigned int accountId,
								  unsigned int pledgeId, unsigned int builder,
								  unsigned int gender, unsigned int race,
								  unsigned int classId, unsigned int world,
								  int x, int y, int z, double hp, double mp,
								  unsigned int sp, unsigned __int64 exp, unsigned int level,
								  int align, unsigned int pk, unsigned int pvp, unsigned int pkPardon,
								  unsigned int uUnk1, unsigned int uUnk2, unsigned int uUnk3, unsigned int uUnk4,
								  unsigned int uUnk5, unsigned int uUnk6, unsigned int uUnk7, unsigned int uUnk8,
								  unsigned int uUnk9, wchar_t *characterTitle, unsigned char *pUnkBuff, unsigned int uUnk10,
								  unsigned int uUnk11, unsigned int uUnk12, unsigned int uUnk13, unsigned int uUnk14,
								  unsigned int uUnk15, unsigned int uUnk16, unsigned int uUnk17, unsigned int uUnk18,
								  unsigned int uUnk19, unsigned int uUnk20, unsigned int uUnk21, unsigned int uUnk22, bool bUnk23)
{
	typedef CUser* (__cdecl *t)(CUser*, wchar_t*, wchar_t*, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								int, int, int, double, double, unsigned int, unsigned __int64, unsigned int,
								int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, wchar_t*, unsigned char*, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
								unsigned int, unsigned int, bool);
	t f = reinterpret_cast<t>(0x8D435C);
	CUser *ret = f(self, characterName, accountName, characterId, accountId, pledgeId, builder, gender, race,
		classId, world, x, y, z, hp, mp, sp, exp, level, align, pk, pvp, pkPardon,
		uUnk1, uUnk2, uUnk3, uUnk4, uUnk5, uUnk6, uUnk7, uUnk8, uUnk9, characterTitle,
		pUnkBuff, uUnk10, uUnk11, uUnk12, uUnk13, uUnk14, uUnk15, uUnk16, uUnk17,
		uUnk18, uUnk19, uUnk20, uUnk21, uUnk22, bUnk23);
	new (&ret->ext) Ext();
	return ret;
}

CUser* __cdecl CUser::Destructor(CUser *self, bool isMemoryFreeUsed)
{
	self->ext.~Ext();
	typedef CUser* (__cdecl *t)(CUser*, bool);
	t f = reinterpret_cast<t>(0x8D33C0);
	return f(self, isMemoryFreeUsed);
}

CUser::Ext::Ext()
{
}

CUser::Ext::~Ext()
{
}

CUser::Ext::BuySell::BuySell()
  : economy2(0),
	storedNpcSdIndex(0),
	storedReply(-1),
	firstBuySell(true),
	fakeSell(false)
{
}

CUser::Ext::BuySell::BuySellList::BuySellList()
  : adena(0),
    id(0),
	itemCount(0)
{
}

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

