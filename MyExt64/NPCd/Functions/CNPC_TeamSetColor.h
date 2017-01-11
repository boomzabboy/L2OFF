
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamSetColor : public NPCFunction {
public:
	CNPC_TeamSetColor();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamSetColor(CNPC *npc, int eventId, int teamId, int color);
};

