
#include <NPCd/Functions/CNPC_GetDbCookieInt.h>
#include <Common/CLog.h>

CNPC_GetDbCookieInt::CNPC_GetDbCookieInt() :
	NPCFunction(L"GetDbCookieInt", &GetDbCookieInt)
{
}

void* CNPC_GetDbCookieInt::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_GetDbCookieInt::SetTypes()
{
	SetReturnType(Type::TYPE_INT64);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetDbCookieInt::GetDbCookieInt(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieInt stub");
	return 0;
}

