
#include <NPCd/Functions/CNPC_DelDbDataById.h>
#include <Common/CLog.h>

CNPC_DelDbDataById::CNPC_DelDbDataById() :
	NPCFunction(L"DelDbDataById", &DelDbDataById)
{
}

void* CNPC_DelDbDataById::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_DelDbDataById::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_DelDbDataById::DelDbDataById(CNPC *npc, int id)
{
    CLog::Add(CLog::Blue, L"CNPC::DelDbDataById stub");
	return 0;
}

