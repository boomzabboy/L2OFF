
#include <NPCd/Functions/CNPC_ChangeNickName.h>
#include <Common/CLog.h>

CNPC_ChangeNickName::CNPC_ChangeNickName() :
	NPCFunction(L"ChangeNickName", &ChangeNickName)
{
}

void* CNPC_ChangeNickName::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_ChangeNickName::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_STRING);
}

int CNPC_ChangeNickName::ChangeNickName(CNPC *npc, CSharedCreatureData *creature, wchar_t *name)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeNickName stub");
	return 0;
}

