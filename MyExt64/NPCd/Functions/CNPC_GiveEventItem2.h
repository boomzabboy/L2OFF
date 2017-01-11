
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GiveEventItem2 : public NPCFunction {
public:
	CNPC_GiveEventItem2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GiveEventItem2(CNPC *npc, CSharedCreatureData *target, int reqItemId, __int64 reqAmount, int giveItemId1, __int64 giveAmount1, int giveItemId2, __int64 giveAmount2, int id, int timeLimit);
};

