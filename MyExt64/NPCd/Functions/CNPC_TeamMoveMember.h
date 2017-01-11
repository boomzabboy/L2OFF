
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeamMoveMember : public NPCFunction {
public:
	CNPC_TeamMoveMember();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamMoveMember(CNPC *npc, int eventId, int teamId, CSharedCreatureData *target);
};

