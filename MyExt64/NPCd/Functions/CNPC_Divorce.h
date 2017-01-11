
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_Divorce : public NPCFunction {
public:
	CNPC_Divorce();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Divorce(CNPC *npc, int charIndex);
};

