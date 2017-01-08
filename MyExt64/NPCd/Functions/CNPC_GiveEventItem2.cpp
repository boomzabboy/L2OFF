
#include <NPCd/Functions/CNPC_GiveEventItem2.h>
#include <Common/CLog.h>

CNPC_GiveEventItem2::CNPC_GiveEventItem2() :
	NPCFunction(L"GiveEventItem2", &GiveEventItem2)
{
}

void* CNPC_GiveEventItem2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8]);
}

void CNPC_GiveEventItem2::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
}

int CNPC_GiveEventItem2::GiveEventItem2(CNPC *npc, CSharedCreatureData *target, int requiredItemId, INT64 requiredAmount, int giveItemId1, INT64 giveAmount1, int giveItemId2, INT64 giveAmount2, int id, int timeLimit)
{
    CLog::Add(CLog::Blue, L"CNPC::GiveEventItem2 stub");
	return 0;
}

