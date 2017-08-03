
#include <Server/CItem.h>
#include <Server/CContributeData.h>
#include <Server/CUser.h>
#include <Common/Utils.h>

void CItem::Init()
{
	WriteMemoryBYTES(0x95B09C, "\x48\x89\xD9", 3);
	WriteInstructionCallJmpEax(0x95B09F, reinterpret_cast<UINT32>(WarehouseDepositHelper));

	WriteInstructionCall(0x8B08D6, FnPtr(&CItem::IsPrivateSellable), 0x8B08DC);
	WriteInstructionCall(0x8B1159, FnPtr(&CItem::IsPrivateSellable), 0x8B115F);
	WriteInstructionCall(0x8B21A2, FnPtr(&CItem::IsPrivateSellable), 0x8B21A8);
	WriteInstructionCall(0x8B27E4, FnPtr(&CItem::IsPrivateSellable), 0x8B27EA);
	WriteInstructionCall(0x8BA5B0, FnPtr(&CItem::IsPrivateSellable), 0x8BA5B6);
	WriteInstructionCall(0x8BB282, FnPtr(&CItem::IsPrivateSellable), 0x8BB288);
	WriteInstructionCall(0x8C83CC, FnPtr(&CItem::IsPrivateSellable), 0x8C83D2);
}

CContributeData* CItem::GetContributeData()
{
	return reinterpret_cast<CContributeData*(*)(UINT32*)>(0x86E3D0)(&contributeDataObjectId);
}

bool CItem::IsTradeable(CUser *user)
{
	return reinterpret_cast<bool(*)(CItem*, CUser*)>(0x6940C0)(this, user);
}

UINT64 __cdecl CItem::WarehouseDepositHelper(CItem *item)
{
	if (item->sd->someType == 2
		|| item->sd->someType == 0x10
		|| item->sd->someType == 0x1a) {

		return 0x95B0AB; // have to check whether item is equipped
	} else {
		return 0x95B10F;
	}
}

bool CItem::IsPrivateSellable(CUser *user, bool b)
{
	if (!GetVfn<bool(*)(CItem*, CUser*, bool)>(this, 0x98)(this, user, b)) {
		return false;
	}
	if (sd->ext.isPrivateStoreSet) {
		return sd->ext.isPrivateStore;
	} else {
		return IsTradeable(user);
	}
}

CompileTimeOffsetCheck(CItem, worldInfo, 0x0048);
CompileTimeOffsetCheck(CItem, contributeDataObjectId, 0x00B8);

