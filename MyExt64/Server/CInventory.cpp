
#include <Server/CInventory.h>
#include <Server/CItem.h>
#include <Server/CCreature.h>
#include <Server/CUser.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CInventory::Init()
{
	WriteInstructionCall(0x875D3B, reinterpret_cast<UINT32>(GetByServerIDIgnoreMoreStacks));
}

CItem* CInventory::GetByServerIDIgnoreMoreStacks(CInventory *self, int id)
{
	CItem *item = reinterpret_cast<CItem*(*)(CInventory*, int)>(0x686D2C)(self, id);
	if (!item || !item->worldInfo || item->worldInfo->consumeType != 2) {
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

