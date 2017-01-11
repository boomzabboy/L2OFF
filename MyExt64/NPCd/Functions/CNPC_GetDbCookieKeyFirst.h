
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieKeyFirst : public NPCFunction {
public:
	CNPC_GetDbCookieKeyFirst();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieKeyFirst(CNPC *npc, CSharedCreatureData *c, int groupId);
};

