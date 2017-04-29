
#include <Server/CInventory.h>
#include <Server/CItem.h>
#include <Server/CCreature.h>
#include <Server/CUser.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CInventory::Init()
{
	WriteInstructionCall(0x875D3B, reinterpret_cast<UINT32>(GetByServerIDIgnoreMoreStacks));
	WriteInstructionCall(0x44F1C0 + 0xE2, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x450010 + 0x57E, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x451704 + 0x2A2, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x4525C8 + 0x1F4, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x5B4118 + 0x922, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x5C3EB8 + 0x8CB, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x5DB408 + 0x856, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x60EF5C + 0x152, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6C0FE4 + 0x11D, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6C8CEC + 0x104, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6C967C + 0x437, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6E333C + 0x14A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6E333C + 0x1E3, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x73A00C + 0x1A2, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x73A00C + 0x1F8, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x746318 + 0xB2A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x747184 + 0xC8E, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x748200 + 0xA2F, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7F9E00 + 0x13F, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7F9E00 + 0x188, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7FE808 + 0x523, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x88ED64 + 0x155, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x88F270 + 0x344, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x88F64C + 0x2B1, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8907AC + 0x68A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x89A830 + 0xCB, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x89B5A8 + 0x198, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8A4F84 + 0x259, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8A58BC + 0x230, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8A5C78 + 0x11E, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8A80B0 + 0x578, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8B0528 + 0xF2A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8B1FE0 + 0xAB8, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8B2C1C + 0x4FD, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8BA18C + 0x789, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8BAA98 + 0xB0B, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C6A54 + 0x524, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C6A54 + 0x932, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C7B10 + 0x43B, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C7B10 + 0xC14, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8CB090 + 0x8B9, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8D8E9C + 0xF2, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8DB5B0 + 0x5EF, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E3BC0 + 0x6C4, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x92F924 + 0x51D, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x931090 + 0xB57, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x948444 + 0x48C, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x948444 + 0x5C3, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x95ADDC + 0x926, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8DA79A, reinterpret_cast<UINT32>(GetFirstItemByClassIDIgnoreMoreStacks));
}

CItem* CInventory::GetByServerIDIgnoreMoreStacks(CInventory *self, int id)
{
	CItem *item = reinterpret_cast<CItem*(*)(CInventory*, int)>(0x686D2C)(self, id);
	if (!item || !item->worldInfo || (item->worldInfo->consumeType != 2 && item->worldInfo->consumeType != 3)) {
		return item;
	}

	CCreature *owner = self->GetOwner();
	if (owner && owner->IsUser()) {
		CUser *user = reinterpret_cast<CUser*>(owner);
		if (user->GetItemCount(item->itemId) != item->worldInfo->count) {
			CLog::Add(CLog::Red, L"User [%s] trying to put multiple item [%d] stacks into trade",
				user->GetName(), item->itemId);
			return 0;
		}
	}

	return item;
}

CCreature* CInventory::GetOwner()
{
	return reinterpret_cast<CCreature*(*)(CInventory*)>(0x6873A0)(this);
}

INT64 CInventory::GetAdenaAmountWrapper(CInventory *self)
{
	return self->GetAdenaAmount();
}

INT64 CInventory::GetAdenaAmount()
{
	INT64 ret = reinterpret_cast<INT64(*)(CInventory*)>(0x687FC8)(this);
	CItem *adenaItem = GetFirstItemByClassID(57, false);
	if (!adenaItem) {
		return 0;
	}
	CCreature *owner = GetOwner();
	if (owner && owner->IsUser()) {
		CUser *user = reinterpret_cast<CUser*>(owner);
		if (user->GetItemCount(57) != adenaItem->worldInfo->count) {
			return 0;
		}
	}
	return ret;
}

CItem* CInventory::GetFirstItemByClassIDIgnoreMoreStacks(CInventory *self, int classId, bool b)
{
	CItem *ret = self->GetFirstItemByClassID(classId, b);
	if (!ret) {
		return 0;
	}
	if (ret->worldInfo->consumeType != 2 && ret->worldInfo->consumeType != 3) {
		return ret;
	}

	CCreature *owner = self->GetOwner();
	if (owner && owner->IsUser()) {
		CUser *user = reinterpret_cast<CUser*>(owner);
		if (user->GetItemCount(ret->itemId) != ret->worldInfo->count) {
			CLog::Add(CLog::Red, L"User [%s] trying to use multiple item [%d] stacks",
				user->GetName(), ret->itemId);
			return 0;
		}
	}
	return ret;
}

CItem* CInventory::GetFirstItemByClassID(int classId, bool b)
{
	return reinterpret_cast<CItem*(*)(CInventory*, int, bool)>(0x688E80)(this, classId, b);
}

