
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamSetRestartPoint : public NPCFunction {
public:
	CNPC_TeamSetRestartPoint();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamSetRestartPoint(CNPC *npc, int eventId, int teamId, int x, int y, int z);
};

