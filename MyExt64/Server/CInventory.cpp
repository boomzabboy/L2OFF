
#include <Server/CInventory.h>
#include <Server/CItem.h>
#include <Server/CCreature.h>
#include <Server/CUser.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CInventory::Init()
{
	WriteInstructionCall(0x875D3B, reinterpret_cast<UINT32>(GetByServerIDIgnoreMoreStacks));
	WriteInstructionCall(0x471D24 + 0x1AA, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x471D24 + 0x4CF, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x47242C + 0x1BE, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x47242C + 0x4E3, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x48D5CC + 0x9F, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x5377A8 + 0xA0, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x63930C + 0xB2, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x689744 + 0x9F, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x689900 + 0x99, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x689A88 + 0xCF, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x68CCEC + 0x298, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x68D4F4 + 0x196, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6F9EEC + 0x137, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x6FA184 + 0x1DB, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x710244 + 0x180, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x730554 + 0xEC, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x751F00 + 0x17A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7B6860 + 0x198, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7F84AC + 0x9D, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7F966C + 0xE6, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x7F9964 + 0x10A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x874410 + 0x507, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x874410 + 0x9E1, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8783EC + 0x2194, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x88ED64 + 0xEE, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x89B5A8 + 0x104, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8AD5A0 + 0x7D, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8B2C1C + 0x259, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C09B4 + 0x245C, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C6A54 + 0xA20, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8C7B10 + 0xCD7, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8D71FC + 0x75, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8D9348 + 0x198, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8D9A20 + 0x10A, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8DA3F0 + 0x3AA, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E4B28 + 0xB7, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E8D54 + 0xC4, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E9640 + 0x4EF, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E9640 + 0xC48, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E9640 + 0x10F4, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8E9640 + 0x1368, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8EF9A8 + 0x1E7, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8F1FAC + 0x100, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x8FF78C + 0x15C, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x916F8C + 0x115, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x94A6E8 + 0x1AC, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x95BC18 + 0x12F4, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
	WriteInstructionCall(0x95D6B4 + 0x1174, reinterpret_cast<UINT32>(GetAdenaAmountWrapper));
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

CItem* CInventory::GetFirstItemByClassID(int classId, bool b)
{
	return reinterpret_cast<CItem*(*)(CInventory*, int, bool)>(0x688E80)(this, classId, b);
}

