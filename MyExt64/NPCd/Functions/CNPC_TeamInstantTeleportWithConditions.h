
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamInstantTeleportWithConditions : public NPCFunction {
public:
	CNPC_TeamInstantTeleportWithConditions();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamInstantTeleportWithConditions(CNPC *npc, int eventId, int teamId, int x, int y, int z, int kickInvalid);
};

