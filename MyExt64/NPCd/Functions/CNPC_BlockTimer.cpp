
#include <NPCd/Functions/CNPC_BlockTimer.h>
#include <Common/CLog.h>

CNPC_BlockTimer::CNPC_BlockTimer() :
	NPCFunction(L"BlockTimer", &BlockTimer)
{
}

void* CNPC_BlockTimer::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_BlockTimer::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_INT);
}

int CNPC_BlockTimer::BlockTimer(CNPC *npc, int timerId)
{
    CLog::Add(CLog::Blue, L"CNPC::BlockTimer stub");
	return 0;
}

