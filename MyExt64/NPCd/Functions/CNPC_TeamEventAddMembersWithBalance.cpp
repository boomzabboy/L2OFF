
#include <NPCd/Functions/CNPC_TeamEventAddMembersWithBalance.h>
#include <Common/CLog.h>

CNPC_TeamEventAddMembersWithBalance::CNPC_TeamEventAddMembersWithBalance() :
	NPCFunction(L"TeamEventAddMembersWithBalance", &TeamEventAddMembersWithBalance)
{
}

void* CNPC_TeamEventAddMembersWithBalance::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_TeamEventAddMembersWithBalance::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INTLIST);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamEventAddMembersWithBalance::TeamEventAddMembersWithBalance(CNPC *npc, int eventId, CIntList *intList, int teamsNumber, int balanceCategoryFrom, int balanceCategoryTo)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamEventAddMembersWithBalance stub");
	return 0;
}

