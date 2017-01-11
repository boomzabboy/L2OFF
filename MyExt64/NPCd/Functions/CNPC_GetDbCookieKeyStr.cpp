
#include <NPCd/Functions/CNPC_GetDbCookieKeyStr.h>
#include <Common/CLog.h>

CNPC_GetDbCookieKeyStr::CNPC_GetDbCookieKeyStr() :
	NPCFunction(L"GetDbCookieKeyStr", &GetDbCookieKeyStr)
{
}

void* CNPC_GetDbCookieKeyStr::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_GetDbCookieKeyStr::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_GetDbCookieKeyStr::GetDbCookieKeyStr(CNPC *npc, CSharedCreatureData *c, int groupId, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieKeyStr stub");
	return 0;
}

