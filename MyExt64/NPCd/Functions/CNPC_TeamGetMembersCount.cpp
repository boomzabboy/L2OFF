
#include <NPCd/Functions/CNPC_TeamGetMembersCount.h>
#include <Common/CLog.h>

CNPC_TeamGetMembersCount::CNPC_TeamGetMembersCount() :
	NPCFunction(L"TeamGetMembersCount", &TeamGetMembersCount)
{
}

void* CNPC_TeamGetMembersCount::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeamGetMembersCount::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamGetMembersCount::TeamGetMembersCount(CNPC *npc, int eventId, int teamId)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamGetMembersCount stub");
	return 0;
}

