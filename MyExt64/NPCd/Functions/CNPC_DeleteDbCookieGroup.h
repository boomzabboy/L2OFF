
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_DeleteDbCookieGroup : public NPCFunction {
public:
	CNPC_DeleteDbCookieGroup();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int DeleteDbCookieGroup(CNPC *npc, CSharedCreatureData *c, int groupId);
};

