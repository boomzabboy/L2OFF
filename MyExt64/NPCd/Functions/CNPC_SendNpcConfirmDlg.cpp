
#include <NPCd/Functions/CNPC_SendNpcConfirmDlg.h>
#include <Common/CLog.h>

CNPC_SendNpcConfirmDlg::CNPC_SendNpcConfirmDlg() :
	NPCFunction(L"SendNpcConfirmDlg", &SendNpcConfirmDlg)
{
}

void* CNPC_SendNpcConfirmDlg::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_SendNpcConfirmDlg::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
}

int CNPC_SendNpcConfirmDlg::SendNpcConfirmDlg(CNPC *npc, int msgId, CSharedCreatureData *c)
{
    CLog::Add(CLog::Blue, L"CNPC::SendNpcConfirmDlg stub");
	return 0;
}

