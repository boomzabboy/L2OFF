
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ChangeNPCState : public NPCFunction {
public:
	CNPC_ChangeNPCState();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeNPCState(CNPC *npc, CSharedCreatureData *creature, int state);
};

