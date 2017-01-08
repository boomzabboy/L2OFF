
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>


class CNPC_FastBuff : public NPCFunction {
public:
	CNPC_FastBuff();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int FastBuff(CNPC *npc, int index, int skillID, int skillLevel);
};

