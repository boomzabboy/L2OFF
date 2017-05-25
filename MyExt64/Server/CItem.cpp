
#include <Server/CItem.h>
#include <Server/CContributeData.h>
#include <Server/CUser.h>
#include <Common/Utils.h>

void CItem::Init()
{
	WriteMemoryBYTES(0x95B09C, "\x48\x89\xD9", 3);
	WriteInstructionCallJmpEax(0x95B09F, reinterpret_cast<UINT32>(WarehouseDepositHelper));

	WriteMemoryDWORD(0x9A3D3D, sizeof(CItem::ItemInfo));
	WriteInstructionCall(0x9A3D58, FnPtr(&CItem::ItemInfo::Constructor));
	WriteMemoryQWORD(0xB63F80, FnPtr(&CItem::ItemInfo::Destructor));

	CompileTimeOffsetCheck(ItemInfo, ext, 0x0198);
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
	if (item->itemInfo->someType == 2
		|| item->itemInfo->someType == 0x10
		|| item->itemInfo->someType == 0x1a) {

		return 0x95B0AB; // have to check whether item is equipped
	} else {
		return 0x95B10F;
	}
}

CItem::ItemInfo* CItem::ItemInfo::Constructor()
{
	ItemInfo *ret = reinterpret_cast<ItemInfo*(*)(ItemInfo*)>(0x69EAAC)(this);
	new (&ret->ext) Ext();
	return ret;
}

void CItem::ItemInfo::Destructor(bool isMemoryFreeUsed)
{
	ext.~Ext();
	reinterpret_cast<void(*)(ItemInfo*, bool)>(0x69ECE4)(this, isMemoryFreeUsed);
}

CItem::ItemInfo::Ext::Ext() : isPrivateStore(false), isPrivateStoreSet(false), isOlympiadCanUse(true)
{
}

CItem::ItemInfo::Ext::~Ext()
{
}

CompileTimeOffsetCheck(CItem, worldInfo, 0x0048);
CompileTimeOffsetCheck(CItem, contributeDataObjectId, 0x00B8);

