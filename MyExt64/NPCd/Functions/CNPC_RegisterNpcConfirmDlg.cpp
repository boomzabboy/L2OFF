
#include <NPCd/Functions/CNPC_RegisterNpcConfirmDlg.h>
#include <Common/CLog.h>

CNPC_RegisterNpcConfirmDlg::CNPC_RegisterNpcConfirmDlg() :
	NPCFunction(L"RegisterNpcConfirmDlg", &RegisterNpcConfirmDlg)
{
}

void* CNPC_RegisterNpcConfirmDlg::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_RegisterNpcConfirmDlg::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_RegisterNpcConfirmDlg::RegisterNpcConfirmDlg(CNPC *npc, int msgId)
{
    CLog::Add(CLog::Blue, L"CNPC::RegisterNpcConfirmDlg stub");
	return 0;
}

