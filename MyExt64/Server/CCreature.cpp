
#include <Server/CCreature.h>
#include <Server/CItem.h>
#include <Server/CUser.h>
#include <Server/CSummon.h>
#include <Server/CUserSocket.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CYieldLock.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/CLog.h>
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

	WriteInstructionCall(0x8DD566, reinterpret_cast<UINT32>(UseItemWrapper));
	WriteMemoryQWORD(0xC54348, reinterpret_cast<UINT64>(UseItemWrapper));
	WriteMemoryQWORD(0xBCCFB8, reinterpret_cast<UINT64>(UseItemWrapper));
	WriteMemoryQWORD(0xBCB888, reinterpret_cast<UINT64>(UseItemWrapper));

	if (Config::Instance()->fixes->territoryWarPetFix) {
		WriteInstructionCall(0x8D1470, reinterpret_cast<UINT32>(GetUserOrMaster), 0x8D1476);
		WriteMemoryBYTES(0x8D1476, "\x4C\x39\xE8", 3);
		WriteMemoryBYTES(0x8D147B,
			"\x44\x8B\x45\x18\x8B\x40\x18\x44"
			"\x89\x44\x24\x30\x89\x44\x24\x20"
			"\x48\x8B\x85\x90\x0A\x00\x00\x8B"
			"\x90\x84\x0B\x00\x00\x89\x54\x24"
			"\x28", 33);
	}

	WriteInstructionCall(0x83B381, reinterpret_cast<UINT32>(UnequipWeaponWrapper), 0x83B387);
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
	if (!this) return false;
	return reinterpret_cast<const UINT64*>(this)[0] == 0xA72FB8;
}

bool CCreature::IsUser() const
{
	if (!this) return false;
	return reinterpret_cast<const UINT64*>(this)[0] == 0xC53BB8;
}

bool CCreature::IsPet() const
{
	if (!this) return false;
	return reinterpret_cast<const UINT64*>(this)[0] == 0xBCC828;
}

bool CCreature::IsSummon() const
{
	if (!this) return false;
	return reinterpret_cast<const UINT64*>(this)[0] == 0xBCB0F8 || IsPet();
}

bool CCreature::IsUserOrSummon() const
{
	return IsUser() || IsSummon();
}

CCreature* __cdecl CCreature::GetUserOrMaster(CCreature *self)
{
	if (self->IsUser()) {
		return self;
	} else if (self->IsSummon()) {
		return reinterpret_cast<CSummon*>(self)->GetUserOrMaster();
	}
	return 0;
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

	return GetCreatureByObjectId(targetId);
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

bool CCreature::UseItem(CItem *item, int i)
{
	GUARDED;

	if (this && item) {
		bool isOlympiad = false;
		if (IsUser()) {
			isOlympiad = reinterpret_cast<CUser*>(this)->IsInOlympiad();
		} else if (IsSummon()) {
			CUser *user = reinterpret_cast<CSummon*>(this)->GetUserOrMaster();
			if (user && user->IsInOlympiad()) {
				isOlympiad = true;
			}
		}

		if (isOlympiad && !item->itemInfo->ext.isOlympiadCanUse) {
			return false;
		}
	}

	if (!reinterpret_cast<bool(*)(CCreature*, CItem*, int)>(0x54C4FC)(this, item, i)) {
		return false;
	}

	if (!this || !IsUser()) {
		return true;
	}

	CUser *user = reinterpret_cast<CUser*>(this);

	if (user->sd && user->sd->protectAfterLoginExpiry) {
		if (!item->itemInfo->itemSkill || !CSkillInfo::escapeSkills.count(item->itemInfo->itemSkill->skillId)) {
			user->sd->protectAfterLoginExpiry = 0;
		}
	}

	if (!user->spiritshotOn || !Config::Instance()->fixes->fixSpiritshotLag) {
		return true;
	}

	if ((item->itemId < 2509 || item->itemId > 2514)
		&& (item->itemId < 3947 || item->itemId > 3952)
		&& item->itemId != 5790
		&& (item->itemId < 22072 || item->itemId > 22081)) {

		return true;
	}

	for (std::vector<CSkillInfo*>::iterator i = item->skills.begin() ; i != item->skills.end() ; ++i) {
		if (!(*i)) {
			continue;
		}
		(*i)->ActivateSkill(this, this, 0, 0, 0, 0);
		user->spiritshotOn = true;
	}

	return true;
}

bool __cdecl CCreature::UseItemWrapper(CCreature *self, CItem *item, int i)
{
	return self->UseItem(item, i);
}

CCreature* CCreature::GetCreatureByObjectId(UINT32 id)
{
	return reinterpret_cast<CCreature*(*)(UINT32*)>(0x86E4E4)(&id);
}

CCreature* CCreature::GetValidCreatureByObjectId(UINT32 id)
{
	GUARDED;

	CCreature *creature = GetCreatureByObjectId(id);
	if (!creature || !creature->IsValidCreature()) {
		return 0;
	}
	return creature;
}

bool CCreature::IsValidCreature() const
{
	switch (reinterpret_cast<UINT32 const *>(this)[0]) {
	case 0xA72FB8: case 0xAB8EC8: case 0xAC87E8: case 0xB1F278: case 0xB7CB18: case 0xB93748:
	case 0xBCB0F8: case 0xBCC828: case 0xC317D8: case 0xC396C8: case 0xC3B568: case 0xC53BB8:
	case 0xC8C148:
		break;
	default:
		return false;
	}
	if (!sd) {
		return false;
	}
	return true;
}

void CCreature::DoNothing()
{
	reinterpret_cast<void(*)(CCreature*)>(0x538FDC)(this);
}

void CCreature::ChangeTarget(CObject *target, int reason)
{
	reinterpret_cast<void(*)(CCreature*, CObject*, int)>(
		(*reinterpret_cast<UINT64**>(this))[0x124])(
			this, target, reason);
}

void __cdecl CCreature::UnequipWeaponWrapper(CCreature *self)
{
	self->UnequipWeapon();
}

void CCreature::UnequipWeapon()
{
	if (IsUser()) {
		if (reinterpret_cast<CUser*>(this)->isCursedUser) {
			return;
		}
	}
	reinterpret_cast<void(*)(CCreature*)>(
		(*reinterpret_cast<void***>(this))[0xF0])(this);
}

bool CCreature::UnequipItem(SlotType slotType)
{
	return reinterpret_cast<bool(*)(CCreature*, SlotType)>(
		(*reinterpret_cast<void***>(this))[0xEF])(this, slotType);
}

UINT32 CCreature::GetServerId()
{
	return reinterpret_cast<UINT32(*)(CCreature*)>(
		(*reinterpret_cast<void***>(this))[0x8C])(this);
}

bool CCreature::IsEnemyTo(CCreature *creature)
{
	return reinterpret_cast<bool(*)(CCreature*, CCreature*)>(
		(*reinterpret_cast<void***>(this))[0x74])(this, creature);
}

void CCreature::BroadcastSkillUse(const int skillId, const int skillLevel, const int hitTime, const int reuseTime)
{
	if (!sd) {
		return;
	}
	double pos[3];
	pos[0] = sd->x;
	pos[1] = sd->y;
	pos[2] = sd->z;
	reinterpret_cast<void(*)(UINT64, CCreature*, int, double*, int, const char*, ...)>(0x421EC8)(
		0x10FF64D8, this, 0x5000, pos, 0xC00, "cddddddddddddd", 0x48,
		objectId, objectId, skillId, skillLevel, hitTime, reuseTime,
		static_cast<INT32>(pos[0]), static_cast<INT32>(pos[1]), static_cast<INT32>(pos[2]),
		0,
		static_cast<INT32>(pos[0]), static_cast<INT32>(pos[1]), static_cast<INT32>(pos[2]));
}

CompileTimeOffsetCheck(CCreature, sdLock, 0x0AA0);
CompileTimeOffsetCheck(CCreature, padding0x1464, 0x1464);

