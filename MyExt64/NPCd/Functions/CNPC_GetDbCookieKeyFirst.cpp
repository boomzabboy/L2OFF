
#include <NPCd/Functions/CNPC_GetDbCookieKeyFirst.h>
#include <Common/CLog.h>

CNPC_GetDbCookieKeyFirst::CNPC_GetDbCookieKeyFirst() :
	NPCFunction(L"GetDbCookieKeyFirst", &GetDbCookieKeyFirst)
{
}

void* CNPC_GetDbCookieKeyFirst::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_GetDbCookieKeyFirst::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetDbCookieKeyFirst::GetDbCookieKeyFirst(CNPC *npc, CSharedCreatureData *c, int groupId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieKeyFirst stub");
	return 0;
}

