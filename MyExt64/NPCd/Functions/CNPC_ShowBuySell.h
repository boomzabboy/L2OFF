
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>
#include <NPCd/CBuySellList.h>

class CNPC_ShowBuySell : public NPCFunction {
public:
	CNPC_ShowBuySell();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ShowBuySell(CNPC *npc, CSharedCreatureData *talker, CBuySellList *buyList, CBuySellList *sellList, float rate);
};

