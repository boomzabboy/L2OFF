
#include <NPCd/Functions/CNPC_Divorce.h>
#include <Common/CLog.h>

CNPC_Divorce::CNPC_Divorce() :
	NPCFunction(L"Divorce", &Divorce)
{
}

void* CNPC_Divorce::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_Divorce::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_Divorce::Divorce(CNPC *npc, int charIndex)
{
    CLog::Add(CLog::Blue, L"CNPC::Divorce stub");
	return 0;
}

