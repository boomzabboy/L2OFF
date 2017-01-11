
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamEventGetTeamsCount : public NPCFunction {
public:
	CNPC_TeamEventGetTeamsCount();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamEventGetTeamsCount(CNPC *npc, int eventId);
};

