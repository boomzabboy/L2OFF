
#include <NPCd/Functions/CNPC_Engage.h>
#include <Common/CLog.h>

CNPC_Engage::CNPC_Engage() :
	NPCFunction(L"Engage", &Engage)
{
}

void* CNPC_Engage::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_Engage::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_Engage::Engage(CNPC *npc, int char1Index, int char2Index)
{
    CLog::Add(CLog::Blue, L"CNPC::Engage stub");
	return 0;
}

