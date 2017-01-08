
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ChangeDir : public NPCFunction {
public:
	CNPC_ChangeDir();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeDir(CNPC *npc, CSharedCreatureData *creature, int targetId, int angle);
};

