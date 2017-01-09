
#include <NPCd/Functions/CNPC_ShowBuySell.h>
#include <Common/CLog.h>

CNPC_ShowBuySell::CNPC_ShowBuySell() :
	NPCFunction(L"ShowBuySell", &ShowBuySell)
{
}

void* CNPC_ShowBuySell::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3]);
}

void CNPC_ShowBuySell::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_BUYSELLLIST);
	AddParameter(Type::TYPE_BUYSELLLIST);
	AddParameter(Type::TYPE_FLOAT);
}

int CNPC_ShowBuySell::ShowBuySell(CNPC *npc, CSharedCreatureData *talker, CBuySellList* buyList, CBuySellList* sellList, float rate)
{
    CLog::Add(CLog::Blue, L"CNPC::ShowBuySell stub");
	return 0;
}

