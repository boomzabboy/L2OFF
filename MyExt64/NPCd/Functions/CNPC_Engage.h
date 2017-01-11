
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_Engage : public NPCFunction {
public:
	CNPC_Engage();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Engage(CNPC *npc, int char1Index, int char2Index);
};

