
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamRemoveAllMembers : public NPCFunction {
public:
	CNPC_TeamRemoveAllMembers();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamRemoveAllMembers(CNPC *npc, int eventId, int teamId);
};

