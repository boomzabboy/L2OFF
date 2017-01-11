
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamSetParticipantConditions : public NPCFunction {
public:
	CNPC_TeamSetParticipantConditions();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamSetParticipantConditions(CNPC *npc, int eventId, int teamId, int conditionMask);
};

