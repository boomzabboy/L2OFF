
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamGetInactiveCharacters : public NPCFunction {
public:
	CNPC_TeamGetInactiveCharacters();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamGetInactiveCharacters(CNPC *npc, int eventId, int teamId, int inactiveTimeSec);
};

