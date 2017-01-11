
#include <NPCd/Functions/CNPC_TeamRemoveAllMembers.h>
#include <Common/CLog.h>

CNPC_TeamRemoveAllMembers::CNPC_TeamRemoveAllMembers() :
	NPCFunction(L"TeamRemoveAllMembers", &TeamRemoveAllMembers)
{
}

void* CNPC_TeamRemoveAllMembers::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeamRemoveAllMembers::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamRemoveAllMembers::TeamRemoveAllMembers(CNPC *npc, int eventId, int teamId)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamRemoveAllMembers stub");
	return 0;
}

