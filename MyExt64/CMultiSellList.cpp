
#include "CMultiSellList.h"
#include "CUser.h"
#include "CNPC.h"
#include "CSharedCreatureData.h"

void CMultiSellList::Init()
{
	WriteInstructionCall(0x7316FE, reinterpret_cast<UINT32>(SendListWrapper));
}

void CMultiSellList::SendListWrapper(CMultiSellList *self, CUser *user, CNPC *npc)
{
	self->SendList(user, npc);
}

void CMultiSellList::SendList(CUser *user, CNPC *npc)
{
	if (!user) {
		return;
	}
	if (!npc) {
		return;
	}
	{
		ScopedLock lock(user->ext.guard.lastMultisellLock);
		user->ext.guard.lastMultisellNpcId = npc->sd->npcClassId;
		user->ext.guard.lastMultisellListId = id;
	}
	reinterpret_cast<void(*)(CMultiSellList*, CUser*, CNPC*)>(0x6FA184)(this, user, npc);
}

