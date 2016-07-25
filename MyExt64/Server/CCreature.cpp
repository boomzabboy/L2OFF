
#include <Server/CCreature.h>
#include <Server/CItem.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CYieldLock.h>
#include <Common/Utils.h>
#include <math.h>

void CCreature::Init()
{
	WriteInstructionCall(0x57362C + 0xC0, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x575B40 + 0x694, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x7130B0 + 0x79, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x7131E8 + 0x9C, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x847364 + 0xA0, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x847364 + 0xBD, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
	WriteInstructionCall(0x895AE0 + 0x79, reinterpret_cast<UINT32>(GetRemainReuseDelaySecWrapper));
}

CCreature::CCreature()
{
}

CCreature::~CCreature()
{
}

int CCreature::GetAcquiredSkillLevel(int skillId)
{ GUARDED

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

bool CCreature::IsUser() const
{
	return reinterpret_cast<const UINT64*>(this)[0] == 0xC53BB8;
}

bool CCreature::IsPet() const
{
	return reinterpret_cast<const UINT64*>(this)[0] == 0xBCC828;
}

bool CCreature::IsSummon() const
{
	return reinterpret_cast<const UINT64*>(this)[0] == 0xBCB0F8 || IsPet();
}

bool CCreature::AddItemToInventory(int itemId, UINT64 count)
{ GUARDED

    UINT32 itemOptionKey[2];
    itemOptionKey[0] = 0;
    itemOptionKey[1] = 0;
    UINT16 baseAttribute[8];
    baseAttribute[0] = 0xfffe;
    for (size_t i = 1 ; i < 8 ; ++i) {
        baseAttribute[i] = 0;
    }
	return reinterpret_cast<bool(*)(CCreature*, int, UINT64, bool, int, int, int, void*, int, void*)>(0x533E44)(
		this, itemId, count, false, 0, 0, 0, reinterpret_cast<void*>(itemOptionKey), 0, reinterpret_cast<void*>(baseAttribute));
}

CCreature* CCreature::GetTarget()
{
	GUARDED;

	CCreature *result = 0;
	UINT32 targetId_ = targetId;
	if (targetId_ && (targetId_ & 0xF8000000) == 0x48000000) {
		return reinterpret_cast<CCreature*(*)(UINT64, UINT32)>(0x41A3A4)(0xF1B250, targetId_);
	}
	return 0;
}

unsigned long CCreature::GetSkillUsedTime(const int skillId)
{
	return reinterpret_cast<unsigned long(*)(CCreature*, const int)>(0x550B9C)(this, skillId);
}

int CCreature::GetRemainReuseDelaySec(const int skillId)
{
	UINT64 skillUsedTime = GetSkillUsedTime(skillId);
	if (!skillUsedTime) {
		return 0;
	}
	INT64 delta = skillUsedTime - GetTickCount();
	if (delta <= 0) {
		return 0;
	}
	return ceil(double(delta) / 1000.0);
}

int __cdecl CCreature::GetRemainReuseDelaySecWrapper(CCreature *self, const int skillId)
{
	return self->GetRemainReuseDelaySec(skillId);
}

CompileTimeOffsetCheck(CCreature, sdLock, 0x0AA0);
CompileTimeOffsetCheck(CCreature, padding0x1464, 0x1464);

