
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieGroupSize : public NPCFunction {
public:
	CNPC_GetDbCookieGroupSize();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieGroupSize(CNPC *npc, CSharedCreatureData *c, int groupId);
};

