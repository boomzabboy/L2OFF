
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_BlockTimer : public NPCFunction {
public:
	CNPC_BlockTimer();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int BlockTimer(CNPC *npc, int timerId);
};

