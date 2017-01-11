
#include <NPCd/Functions/CNPC_TeamGetMemberByIndex.h>
#include <Common/CLog.h>

CNPC_TeamGetMemberByIndex::CNPC_TeamGetMemberByIndex() :
	NPCFunction(L"TeamGetMemberByIndex", &TeamGetMemberByIndex)
{
}

void* CNPC_TeamGetMemberByIndex::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamGetMemberByIndex::SetTypes()
{
	SetReturnType(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamGetMemberByIndex::TeamGetMemberByIndex(CNPC *npc, int eventId, int teamId, int memberIndex)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamGetMemberByIndex stub");
	return 0;
}

