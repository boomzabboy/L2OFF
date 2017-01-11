
#include <NPCd/Functions/CNPC_GetDbCookieKeyNext.h>
#include <Common/CLog.h>

CNPC_GetDbCookieKeyNext::CNPC_GetDbCookieKeyNext() :
	NPCFunction(L"GetDbCookieKeyNext", &GetDbCookieKeyNext)
{
}

void* CNPC_GetDbCookieKeyNext::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_GetDbCookieKeyNext::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetDbCookieKeyNext::GetDbCookieKeyNext(CNPC *npc, CSharedCreatureData *c, int groupId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieKeyNext stub");
	return 0;
}

