
#include <NPCd/Functions/CNPC_TeamMoveMember.h>
#include <Common/CLog.h>

CNPC_TeamMoveMember::CNPC_TeamMoveMember() :
	NPCFunction(L"TeamMoveMember", &TeamMoveMember)
{
}

void* CNPC_TeamMoveMember::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamMoveMember::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_TeamMoveMember::TeamMoveMember(CNPC *npc, int eventId, int teamId, CSharedCreatureData *target)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamMoveMember stub");
	return 0;
}

