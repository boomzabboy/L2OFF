
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_IncreaseNPCLogByID : public NPCFunction {
public:
	CNPC_IncreaseNPCLogByID();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int IncreaseNPCLogByID(CNPC *npc, CSharedCreatureData *target, int questId, int questState, int npcId, int maxValue);
};

