
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetNPCLogByID : public NPCFunction {
public:
	CNPC_GetNPCLogByID();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetNPCLogByID(CNPC *npc, CSharedCreatureData *talker, int questId, int questState, int npcId);
};

