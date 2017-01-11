
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeamRemoveMember : public NPCFunction {
public:
	CNPC_TeamRemoveMember();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamRemoveMember(CNPC *npc, CSharedCreatureData *target);
};

