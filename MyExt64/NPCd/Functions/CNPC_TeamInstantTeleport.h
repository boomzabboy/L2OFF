
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamInstantTeleport : public NPCFunction {
public:
	CNPC_TeamInstantTeleport();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamInstantTeleport(CNPC *npc, int eventId, int teamId, int x, int y, int z);
};

