
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamGetMembersCount : public NPCFunction {
public:
	CNPC_TeamGetMembersCount();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamGetMembersCount(CNPC *npc, int eventId, int teamId);
};

