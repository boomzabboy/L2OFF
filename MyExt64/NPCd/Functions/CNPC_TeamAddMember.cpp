
#include <NPCd/Functions/CNPC_TeamAddMember.h>
#include <Common/CLog.h>

CNPC_TeamAddMember::CNPC_TeamAddMember() :
	NPCFunction(L"TeamAddMember", &TeamAddMember)
{
}

void* CNPC_TeamAddMember::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamAddMember::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_TeamAddMember::TeamAddMember(CNPC *npc, int eventId, int teamId, CSharedCreatureData *target)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamAddMember stub");
	return 0;
}

