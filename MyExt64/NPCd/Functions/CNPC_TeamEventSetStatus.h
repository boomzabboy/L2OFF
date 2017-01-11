
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamEventSetStatus : public NPCFunction {
public:
	CNPC_TeamEventSetStatus();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamEventSetStatus(CNPC *npc, int eventId, int status);
};

