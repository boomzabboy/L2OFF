
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieKeyNext : public NPCFunction {
public:
	CNPC_GetDbCookieKeyNext();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieKeyNext(CNPC *npc, CSharedCreatureData *c, int groupId);
};

