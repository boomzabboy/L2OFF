
#include <NPCd/Functions/CNPC_FixMoveType.h>
#include <Common/CLog.h>

CNPC_FixMoveType::CNPC_FixMoveType() :
	NPCFunction(L"FixMoveType", &FixMoveType)
{
}

void* CNPC_FixMoveType::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_FixMoveType::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_FixMoveType::FixMoveType(CNPC *npc, bool block)
{
    CLog::Add(CLog::Blue, L"CNPC::FixMoveType stub");
	return 0;
}

