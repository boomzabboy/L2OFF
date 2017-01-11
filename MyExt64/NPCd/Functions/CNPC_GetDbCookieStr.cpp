
#include <NPCd/Functions/CNPC_GetDbCookieStr.h>
#include <Common/CLog.h>

CNPC_GetDbCookieStr::CNPC_GetDbCookieStr() :
	NPCFunction(L"GetDbCookieStr", &GetDbCookieStr)
{
}

void* CNPC_GetDbCookieStr::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_GetDbCookieStr::SetTypes()
{
	SetReturnType(Type::TYPE_STRING);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetDbCookieStr::GetDbCookieStr(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieStr stub");
	return 0;
}

