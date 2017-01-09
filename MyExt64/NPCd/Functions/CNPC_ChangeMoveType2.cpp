
#include <NPCd/Functions/CNPC_ChangeMoveType2.h>
#include <Common/CLog.h>

CNPC_ChangeMoveType2::CNPC_ChangeMoveType2() :
	NPCFunction(L"ChangeMoveType2", &ChangeMoveType2)
{
}

void* CNPC_ChangeMoveType2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_ChangeMoveType2::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_ChangeMoveType2::ChangeMoveType2(CNPC *npc, int moveType, int force)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeMoveType2 stub");
	return 0;
}

