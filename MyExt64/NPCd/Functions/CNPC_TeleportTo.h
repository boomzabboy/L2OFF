
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeleportTo : public NPCFunction {
public:
	CNPC_TeleportTo();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeleportTo(CNPC *npc, CSharedCreatureData *target1, CSharedCreatureData *target2);
};

