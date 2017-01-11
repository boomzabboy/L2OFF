
#include <NPCd/Functions/CNPC_DeleteDbCookieGroup.h>
#include <Common/CLog.h>

CNPC_DeleteDbCookieGroup::CNPC_DeleteDbCookieGroup() :
	NPCFunction(L"DeleteDbCookieGroup", &DeleteDbCookieGroup)
{
}

void* CNPC_DeleteDbCookieGroup::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_DeleteDbCookieGroup::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_DeleteDbCookieGroup::DeleteDbCookieGroup(CNPC *npc, CSharedCreatureData *c, int groupId)
{
    CLog::Add(CLog::Blue, L"CNPC::DeleteDbCookieGroup stub");
	return 0;
}

