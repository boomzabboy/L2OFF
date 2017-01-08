
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>


class CNPC_ChangeMoveType2 : public NPCFunction {
public:
	CNPC_ChangeMoveType2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeMoveType2(CNPC *npc, int moveType, int force);
};

