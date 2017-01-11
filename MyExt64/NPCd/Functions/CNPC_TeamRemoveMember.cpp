
#include <NPCd/Functions/CNPC_TeamRemoveMember.h>
#include <Common/CLog.h>

CNPC_TeamRemoveMember::CNPC_TeamRemoveMember() :
	NPCFunction(L"TeamRemoveMember", &TeamRemoveMember)
{
}

void* CNPC_TeamRemoveMember::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_TeamRemoveMember::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_TeamRemoveMember::TeamRemoveMember(CNPC *npc, CSharedCreatureData *target)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamRemoveMember stub");
	return 0;
}

