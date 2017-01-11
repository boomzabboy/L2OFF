
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieStr : public NPCFunction {
public:
	CNPC_GetDbCookieStr();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieStr(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId);
};

