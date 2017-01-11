
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_LoadDbCookieGroup : public NPCFunction {
public:
	CNPC_LoadDbCookieGroup();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int LoadDbCookieGroup(CNPC *npc, CSharedCreatureData *c, int groupId);
};

