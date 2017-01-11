
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_TeamSetMemberColor : public NPCFunction {
public:
	CNPC_TeamSetMemberColor();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamSetMemberColor(CNPC *npc, CSharedCreatureData *target, int color);
};

