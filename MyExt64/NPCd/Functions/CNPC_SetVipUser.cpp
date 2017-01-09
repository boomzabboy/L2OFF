
#include <NPCd/Functions/CNPC_SetVipUser.h>
#include <Common/CLog.h>

CNPC_SetVipUser::CNPC_SetVipUser() :
	NPCFunction(L"SetVipUser", &SetVipUser)
{
}

void* CNPC_SetVipUser::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_SetVipUser::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_SetVipUser::SetVipUser(CNPC *npc, CSharedCreatureData *talker, int duration, int param1, int param2, wchar_t *param3)
{
    CLog::Add(CLog::Blue, L"CNPC::SetVipUser stub");
	return 0;
}

