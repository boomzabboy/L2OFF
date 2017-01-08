
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ChangeUserTalkTarget : public NPCFunction {
public:
	CNPC_ChangeUserTalkTarget();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeUserTalkTarget(CNPC *npc, CSharedCreatureData *target);
};

