
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GiveEventItem2 : public NPCFunction {
public:
	CNPC_GiveEventItem2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GiveEventItem2(CNPC *npc, CSharedCreatureData *target, int requiredItemId, INT64 requiredAmount, int giveItemId1, INT64 giveAmount1, int giveItemId2, INT64 giveAmount2, int id, int timeLimit);
};

