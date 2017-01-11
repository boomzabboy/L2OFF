
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeamAddMember : public NPCFunction {
public:
	CNPC_TeamAddMember();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamAddMember(CNPC *npc, int eventId, int teamId, CSharedCreatureData *target);
};

