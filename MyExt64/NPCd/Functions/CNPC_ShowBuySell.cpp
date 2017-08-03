
#include <NPCd/Functions/CNPC_ShowBuySell.h>
#include <NPCd/NPCd.h>
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

int CNPC_ShowBuySell::ShowBuySell(CNPC *npc, CSharedCreatureData *talker, CBuySellList *sellList, CBuySellList *buyList, float rate)
{
	if (!talker || !buyList || !sellList) {
		return 0;
	}
	if (!reinterpret_cast<bool(*)(CBuySellList*)>(0x555EF8)(buyList)) {
		reinterpret_cast<bool(*)(CBuySellList*)>(0x556BA8)(buyList);
	}
	if (!reinterpret_cast<bool(*)(CBuySellList*)>(0x555EF8)(sellList)) {
		reinterpret_cast<bool(*)(CBuySellList*)>(0x556BA8)(sellList);
	}
	NPCd::Send("chddddf", 0x36, NPCd::SHOW_BUY_SELL,
		npc->sm->index, talker->index, buyList, sellList, rate);
	return 0;
}

