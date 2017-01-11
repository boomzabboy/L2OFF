
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamEventGetStatus : public NPCFunction {
public:
	CNPC_TeamEventGetStatus();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamEventGetStatus(CNPC *npc, int eventId);
};

