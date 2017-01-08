
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SetAttackable : public NPCFunction {
public:
	CNPC_SetAttackable();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetAttackable(CNPC *npc, CSharedCreatureData *creature, int attackable);
};

