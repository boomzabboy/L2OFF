
#include <NPCd/Functions/CNPC_TeamEventGetTeamsCount.h>
#include <Common/CLog.h>

CNPC_TeamEventGetTeamsCount::CNPC_TeamEventGetTeamsCount() :
	NPCFunction(L"TeamEventGetTeamsCount", &TeamEventGetTeamsCount)
{
}

void* CNPC_TeamEventGetTeamsCount::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_TeamEventGetTeamsCount::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamEventGetTeamsCount::TeamEventGetTeamsCount(CNPC *npc, int eventId)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamEventGetTeamsCount stub");
	return 0;
}

