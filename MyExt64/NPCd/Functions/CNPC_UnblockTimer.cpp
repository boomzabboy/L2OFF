
#include <NPCd/Functions/CNPC_UnblockTimer.h>
#include <Common/CLog.h>

CNPC_UnblockTimer::CNPC_UnblockTimer() :
	NPCFunction(L"UnblockTimer", &UnblockTimer)
{
}

void* CNPC_UnblockTimer::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_UnblockTimer::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_UnblockTimer::UnblockTimer(CNPC *npc, int timerId)
{
    CLog::Add(CLog::Blue, L"CNPC::UnblockTimer stub");
	return 0;
}

