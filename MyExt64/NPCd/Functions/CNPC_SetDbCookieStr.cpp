
#include <NPCd/Functions/CNPC_SetDbCookieStr.h>
#include <Common/CLog.h>

CNPC_SetDbCookieStr::CNPC_SetDbCookieStr() :
	NPCFunction(L"SetDbCookieStr", &SetDbCookieStr)
{
}

void* CNPC_SetDbCookieStr::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3]);
}

void CNPC_SetDbCookieStr::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_SetDbCookieStr::SetDbCookieStr(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CNPC::SetDbCookieStr stub");
	return 0;
}

