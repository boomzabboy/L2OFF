
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamEventSetParticipantConditions : public NPCFunction {
public:
	CNPC_TeamEventSetParticipantConditions();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamEventSetParticipantConditions(CNPC *npc, int eventId, int conditionMask);
};

