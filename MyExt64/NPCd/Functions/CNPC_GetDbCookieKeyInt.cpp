
#include <NPCd/Functions/CNPC_GetDbCookieKeyInt.h>
#include <Common/CLog.h>

CNPC_GetDbCookieKeyInt::CNPC_GetDbCookieKeyInt() :
	NPCFunction(L"GetDbCookieKeyInt", &GetDbCookieKeyInt)
{
}

void* CNPC_GetDbCookieKeyInt::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_GetDbCookieKeyInt::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT64);
}

int CNPC_GetDbCookieKeyInt::GetDbCookieKeyInt(CNPC *npc, CSharedCreatureData *c, int groupId, __int64 value)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieKeyInt stub");
	return 0;
}

