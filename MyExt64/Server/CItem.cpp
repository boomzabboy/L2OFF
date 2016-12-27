
#include <Server/CItem.h>
#include <Server/CContributeData.h>
#include <Common/Utils.h>

void CItem::Init()
{
	WriteMemoryBYTES(0x95B09C, "\x48\x89\xD9", 3);
	WriteInstructionCallJmpEax(0x95B09F, reinterpret_cast<UINT32>(WarehouseDepositHelper));
}

CContributeData* CItem::GetContributeData()
{
	return reinterpret_cast<CContributeData*(*)(UINT32*)>(0x86E3D0)(&contributeDataObjectId);
}

UINT64 __cdecl CItem::WarehouseDepositHelper(CItem *item)
{
	if (item->itemInfo->someType == 2
		|| item->itemInfo->someType == 0x10
		|| item->itemInfo->someType == 0x1a) {

		return 0x95B0AB; // have to check whether item is equipped
	} else {
		return 0x95B10F;
	}
}

CompileTimeOffsetCheck(CItem, worldInfo, 0x0048);
CompileTimeOffsetCheck(CItem, contributeDataObjectId, 0x00B8);

