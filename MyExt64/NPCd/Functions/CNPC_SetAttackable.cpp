
#include <NPCd/Functions/CNPC_SetAttackable.h>
#include <Common/CLog.h>

CNPC_SetAttackable::CNPC_SetAttackable() :
	NPCFunction(L"SetAttackable", &SetAttackable)
{
}

void* CNPC_SetAttackable::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_SetAttackable::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
}

int CNPC_SetAttackable::SetAttackable(CNPC *npc, CSharedCreatureData *creature, int attackable)
{
    CLog::Add(CLog::Blue, L"CNPC::SetAttackable stub");
	return 0;
}

