
#include <NPCd/Functions/CNPC_ChangeDir.h>
#include <Common/CLog.h>

CNPC_ChangeDir::CNPC_ChangeDir() :
	NPCFunction(L"ChangeDir", &ChangeDir)
{
}

void* CNPC_ChangeDir::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_ChangeDir::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_ChangeDir::ChangeDir(CNPC *npc, CSharedCreatureData *creature, int targetId, int angle)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeDir stub");
	return 0;
}

