
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>


class CNPC_UnBlockTimer : public NPCFunction {
public:
	CNPC_UnBlockTimer();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int UnBlockTimer(CNPC *npc, int timerId);
};

