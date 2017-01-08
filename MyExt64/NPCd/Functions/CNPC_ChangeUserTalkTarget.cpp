
#include <NPCd/Functions/CNPC_ChangeUserTalkTarget.h>
#include <Common/CLog.h>

CNPC_ChangeUserTalkTarget::CNPC_ChangeUserTalkTarget() :
	NPCFunction(L"ChangeUserTalkTarget", &ChangeUserTalkTarget)
{
}

void* CNPC_ChangeUserTalkTarget::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_ChangeUserTalkTarget::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
}

int CNPC_ChangeUserTalkTarget::ChangeUserTalkTarget(CNPC *npc, CSharedCreatureData *target)
{
    CLog::Add(CLog::Blue, L"CNPC::ChangeUserTalkTarget stub");
	return 0;
}

