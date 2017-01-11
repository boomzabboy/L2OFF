
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_UnblockTimer : public NPCFunction {
public:
	CNPC_UnblockTimer();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int UnblockTimer(CNPC *npc, int timerId);
};

