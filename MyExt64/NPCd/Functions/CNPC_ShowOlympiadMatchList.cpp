
#include <NPCd/Functions/CNPC_ShowOlympiadMatchList.h>
#include <Common/CLog.h>

CNPC_ShowOlympiadMatchList::CNPC_ShowOlympiadMatchList() :
	NPCFunction(L"ShowOlympiadMatchList", &ShowOlympiadMatchList)
{
}

void* CNPC_ShowOlympiadMatchList::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_ShowOlympiadMatchList::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
}

int CNPC_ShowOlympiadMatchList::ShowOlympiadMatchList(CNPC *npc, CSharedCreatureData *creature)
{
    CLog::Add(CLog::Blue, L"CNPC::ShowOlympiadMatchList stub");
	return 0;
}

