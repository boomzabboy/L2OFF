
#include <NPCd/Functions/CNPC_SetAbilityItemDrop.h>
#include <NPCd/NPCd.h>
#include <Common/CLog.h>

CNPC_SetAbilityItemDrop::CNPC_SetAbilityItemDrop() :
	NPCFunction(L"SetAbilityItemDrop", &SetAbilityItemDrop)
{
}

void* CNPC_SetAbilityItemDrop::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_SetAbilityItemDrop::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_SetAbilityItemDrop::SetAbilityItemDrop(CNPC *npc, int canDrop)
{
	NPCd::Send("chdc", 0x36, NPCd::SET_ABILITY_ITEM_DROP, npc->sm->index, canDrop ? 1 : 0);
	return 0;
}

