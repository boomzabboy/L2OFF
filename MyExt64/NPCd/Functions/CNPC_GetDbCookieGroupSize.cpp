
#include <NPCd/Functions/CNPC_GetDbCookieGroupSize.h>
#include <Common/CLog.h>

CNPC_GetDbCookieGroupSize::CNPC_GetDbCookieGroupSize() :
	NPCFunction(L"GetDbCookieGroupSize", &GetDbCookieGroupSize)
{
}

void* CNPC_GetDbCookieGroupSize::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_GetDbCookieGroupSize::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetDbCookieGroupSize::GetDbCookieGroupSize(CNPC *npc, CSharedCreatureData *c, int groupId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbCookieGroupSize stub");
	return 0;
}

