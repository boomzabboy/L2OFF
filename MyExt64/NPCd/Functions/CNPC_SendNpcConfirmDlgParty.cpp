
#include <NPCd/Functions/CNPC_SendNpcConfirmDlgParty.h>
#include <Common/CLog.h>

CNPC_SendNpcConfirmDlgParty::CNPC_SendNpcConfirmDlgParty() :
	NPCFunction(L"SendNpcConfirmDlgParty", &SendNpcConfirmDlgParty)
{
}

void* CNPC_SendNpcConfirmDlgParty::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_SendNpcConfirmDlgParty::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_SendNpcConfirmDlgParty::SendNpcConfirmDlgParty(CNPC *npc, int msgId, CSharedCreatureData *c)
{
    CLog::Add(CLog::Blue, L"CNPC::SendNpcConfirmDlgParty stub");
	return 0;
}

