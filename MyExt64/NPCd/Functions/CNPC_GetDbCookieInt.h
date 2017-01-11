
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieInt : public NPCFunction {
public:
	CNPC_GetDbCookieInt();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieInt(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId);
};

