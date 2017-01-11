
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_SetAbilityItemDrop : public NPCFunction {
public:
	CNPC_SetAbilityItemDrop();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetAbilityItemDrop(CNPC *npc, int canDrop);
};

