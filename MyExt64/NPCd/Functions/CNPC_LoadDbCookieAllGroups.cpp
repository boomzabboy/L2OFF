
#include <NPCd/Functions/CNPC_LoadDbCookieAllGroups.h>
#include <Common/CLog.h>

CNPC_LoadDbCookieAllGroups::CNPC_LoadDbCookieAllGroups() :
	NPCFunction(L"LoadDbCookieAllGroups", &LoadDbCookieAllGroups)
{
}

void* CNPC_LoadDbCookieAllGroups::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_LoadDbCookieAllGroups::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_LoadDbCookieAllGroups::LoadDbCookieAllGroups(CNPC *npc, CSharedCreatureData *c)
{
    CLog::Add(CLog::Blue, L"CNPC::LoadDbCookieAllGroups stub");
	return 0;
}

