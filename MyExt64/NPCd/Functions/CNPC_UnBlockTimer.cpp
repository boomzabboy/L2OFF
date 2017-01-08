
#include <NPCd/Functions/CNPC_UnBlockTimer.h>
#include <Common/CLog.h>

CNPC_UnBlockTimer::CNPC_UnBlockTimer() :
	NPCFunction(L"UnBlockTimer", &UnBlockTimer)
{
}

void* CNPC_UnBlockTimer::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_UnBlockTimer::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_INT);
}

int CNPC_UnBlockTimer::UnBlockTimer(CNPC *npc, int timerId)
{
    CLog::Add(CLog::Blue, L"CNPC::UnBlockTimer stub");
	return 0;
}

