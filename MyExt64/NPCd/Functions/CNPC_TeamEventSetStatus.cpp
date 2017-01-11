
#include <NPCd/Functions/CNPC_TeamEventSetStatus.h>
#include <Common/CLog.h>

CNPC_TeamEventSetStatus::CNPC_TeamEventSetStatus() :
	NPCFunction(L"TeamEventSetStatus", &TeamEventSetStatus)
{
}

void* CNPC_TeamEventSetStatus::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeamEventSetStatus::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamEventSetStatus::TeamEventSetStatus(CNPC *npc, int eventId, int status)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamEventSetStatus stub");
	return 0;
}

