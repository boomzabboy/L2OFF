
#include <NPCd/Functions/CNPC_DeleteDbCookie.h>
#include <Common/CLog.h>

CNPC_DeleteDbCookie::CNPC_DeleteDbCookie() :
	NPCFunction(L"DeleteDbCookie", &DeleteDbCookie)
{
}

void* CNPC_DeleteDbCookie::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_DeleteDbCookie::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_DeleteDbCookie::DeleteDbCookie(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId)
{
    CLog::Add(CLog::Blue, L"CNPC::DeleteDbCookie stub");
	return 0;
}

