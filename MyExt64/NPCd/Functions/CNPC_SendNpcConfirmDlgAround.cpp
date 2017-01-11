
#include <NPCd/Functions/CNPC_SendNpcConfirmDlgAround.h>
#include <Common/CLog.h>

CNPC_SendNpcConfirmDlgAround::CNPC_SendNpcConfirmDlgAround() :
	NPCFunction(L"SendNpcConfirmDlgAround", &SendNpcConfirmDlgAround)
{
}

void* CNPC_SendNpcConfirmDlgAround::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_SendNpcConfirmDlgAround::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_SendNpcConfirmDlgAround::SendNpcConfirmDlgAround(CNPC *npc, int msgId, CSharedCreatureData *c, int range, int userLevelMin, int userLevelMax)
{
    CLog::Add(CLog::Blue, L"CNPC::SendNpcConfirmDlgAround stub");
	return 0;
}

