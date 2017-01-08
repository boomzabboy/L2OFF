
#include <NPCd/Functions/CNPC_TeleportTo.h>
#include <Common/CLog.h>

CNPC_TeleportTo::CNPC_TeleportTo() :
	NPCFunction(L"TeleportTo", &TeleportTo)
{
}

void* CNPC_TeleportTo::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeleportTo::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_CREATURE);
}

int CNPC_TeleportTo::TeleportTo(CNPC *npc, CSharedCreatureData *target1, CSharedCreatureData *target2)
{
    CLog::Add(CLog::Blue, L"CNPC::TeleportTo stub");
	return 0;
}

