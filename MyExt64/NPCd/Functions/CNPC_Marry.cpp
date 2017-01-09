
#include <NPCd/Functions/CNPC_Marry.h>
#include <Common/CLog.h>

CNPC_Marry::CNPC_Marry() :
	NPCFunction(L"Marry", &Marry)
{
}

void* CNPC_Marry::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_Marry::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_Marry::Marry(CNPC *npc, int charIndex1, int charIndex2)
{
    CLog::Add(CLog::Blue, L"CNPC::Marry stub");
	return 0;
}

