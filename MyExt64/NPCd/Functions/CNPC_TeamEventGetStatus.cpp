
#include <NPCd/Functions/CNPC_TeamEventGetStatus.h>
#include <Common/CLog.h>

CNPC_TeamEventGetStatus::CNPC_TeamEventGetStatus() :
	NPCFunction(L"TeamEventGetStatus", &TeamEventGetStatus)
{
}

void* CNPC_TeamEventGetStatus::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_TeamEventGetStatus::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamEventGetStatus::TeamEventGetStatus(CNPC *npc, int eventId)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamEventGetStatus stub");
	return 0;
}

