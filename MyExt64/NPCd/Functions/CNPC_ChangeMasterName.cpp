
#include <NPCd/Functions/CNPC_ChangeMasterName.h>
#include <Common/CLog.h>

CNPC_ChangeMasterName::CNPC_ChangeMasterName() :
	NPCFunction(L"ChangeMasterName", &ChangeMasterName)
{
}

void* CNPC_ChangeMasterName::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_ChangeMasterName::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_ChangeMasterName::ChangeMasterName(CNPC *npc, CSharedCreatureData *talker, wchar_t *name)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeMasterName stub");
	return 0;
}

