
#include <Server/CDB.h>
#include <Server/CUser.h>
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/CSharedCreatureData.h>

void CDB::Init()
{
	WriteInstructionCall(0x443F58 + 0x11D, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x51EB88 + 0x11F, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x55CC2C + 0x2BF, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x562BFC + 0x1C1, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x576DD4 + 0x14C, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x577490 + 0x16C, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x76A03C + 0x112, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x771B94 + 0x13E, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x838AB8 + 0xFF, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x838C30 + 0xFF, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x838DA8 + 0xFF, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x839120 + 0x119, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x883F98 + 0x12B, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x88BE18 + 0xC2, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x899314 + 0x170, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8994DC + 0x161, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8A71A4 + 0x7C1, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8BE4C8 + 0x4B5, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8C09B4 + 0x2089, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8C09B4 + 0x23A9, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8C09B4 + 0x24E7, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8CB090 + 0x30B, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8D0640 + 0x19CF, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8EB694 + 0x26A, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x8F2664 + 0x85, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
	WriteInstructionCall(0x909858 + 0x219, reinterpret_cast<UINT32>(SendSaveCharacterInfoWrapper));
}

CDB::CDB()
{
}

CDB::CDB(const CDB &other)
{
}

CDB::~CDB()
{
}

CDB* CDB::Instance()
{
	return reinterpret_cast<CDB*>(0x149AE80);
}

void CDB::RequestMarkInZoneRestriction(UINT32 userDbId, UINT32 zoneId, UINT32 time, UINT32 count, bool b, UINT32 i)
{
	reinterpret_cast<void(*)(CDB*, UINT32, UINT32, UINT32, UINT32, bool, UINT32)>(0x594D3C)(
		this, userDbId, zoneId, time, count, b, i);
}

void CDB::RequestLoadUserPoint(class CUser *user, int type)
{
	reinterpret_cast<void(*)(CDB*, class CUser*, int)>(0x59145C)(this, user, type);
}

void __cdecl CDB::SendSaveCharacterInfoWrapper(CDB *self, CUser *user, bool a, bool b)
{
	self->SendSaveCharacterInfo(user, a, b);
}

void CDB::SendSaveCharacterInfo(CUser *user, bool a, bool b)
{
	if (user && user->sd) {
		bool skip = false;
		{
			ScopedLock lock(user->ext.cs);
			if (!user->ext.famePointLoaded) {
				skip = true;
			}
		}
		if (skip) {
			CLog::Add(CLog::Red,
				L"User [%s]: can't save character: fame points not loaded yet (requesting load again)",
				user->sd->name);
			RequestLoadUserPoint(user, 5);
			return;
		}
	}
	reinterpret_cast<void(*)(CDB*, CUser*, bool, bool)>(0x5994C4)(this, user, a, b);
}

