
#include <NPCd/Functions/CNPC_ChangeNPCState.h>
#include <Common/CLog.h>

CNPC_ChangeNPCState::CNPC_ChangeNPCState() :
	NPCFunction(L"ChangeNPCState", &ChangeNPCState)
{
}

void* CNPC_ChangeNPCState::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_ChangeNPCState::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
}

int CNPC_ChangeNPCState::ChangeNPCState(CNPC *npc, CSharedCreatureData *creature, int state)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeNPCState stub");
	return 0;
}

