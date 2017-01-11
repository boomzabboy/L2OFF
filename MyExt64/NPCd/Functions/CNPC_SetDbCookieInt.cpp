
#include <NPCd/Functions/CNPC_SetDbCookieInt.h>
#include <Common/CLog.h>

CNPC_SetDbCookieInt::CNPC_SetDbCookieInt() :
	NPCFunction(L"SetDbCookieInt", &SetDbCookieInt)
{
}

void* CNPC_SetDbCookieInt::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3]);
}

void CNPC_SetDbCookieInt::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT64);
}

int CNPC_SetDbCookieInt::SetDbCookieInt(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId, __int64 value)
{
    CLog::Add(CLog::Blue, L"CNPC::SetDbCookieInt stub");
	return 0;
}

