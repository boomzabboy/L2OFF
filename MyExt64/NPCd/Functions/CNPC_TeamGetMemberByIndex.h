
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeamGetMemberByIndex : public NPCFunction {
public:
	CNPC_TeamGetMemberByIndex();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamGetMemberByIndex(CNPC *npc, int eventId, int teamId, int memberIndex);
};

