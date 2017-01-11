
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_Marry : public NPCFunction {
public:
	CNPC_Marry();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Marry(CNPC *npc, int char1Index, int char2Index);
};

