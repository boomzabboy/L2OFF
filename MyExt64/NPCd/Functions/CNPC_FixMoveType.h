
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>


class CNPC_FixMoveType : public NPCFunction {
public:
	CNPC_FixMoveType();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int FixMoveType(CNPC *npc, int block);
};

