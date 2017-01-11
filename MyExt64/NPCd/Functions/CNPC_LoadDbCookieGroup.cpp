
#include <NPCd/Functions/CNPC_LoadDbCookieGroup.h>
#include <Common/CLog.h>

CNPC_LoadDbCookieGroup::CNPC_LoadDbCookieGroup() :
	NPCFunction(L"LoadDbCookieGroup", &LoadDbCookieGroup)
{
}

void* CNPC_LoadDbCookieGroup::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_LoadDbCookieGroup::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_LoadDbCookieGroup::LoadDbCookieGroup(CNPC *npc, CSharedCreatureData *c, int groupId)
{
    CLog::Add(CLog::Blue, L"CNPC::LoadDbCookieGroup stub");
	return 0;
}

