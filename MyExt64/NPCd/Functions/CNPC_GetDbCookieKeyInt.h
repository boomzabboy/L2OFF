
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieKeyInt : public NPCFunction {
public:
	CNPC_GetDbCookieKeyInt();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieKeyInt(CNPC *npc, CSharedCreatureData *c, int groupId, __int64 value);
};

