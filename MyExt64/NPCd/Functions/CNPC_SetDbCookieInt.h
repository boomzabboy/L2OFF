
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SetDbCookieInt : public NPCFunction {
public:
	CNPC_SetDbCookieInt();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetDbCookieInt(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId, __int64 value);
};

