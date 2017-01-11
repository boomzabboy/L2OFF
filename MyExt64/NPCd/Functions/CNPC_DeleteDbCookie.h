
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_DeleteDbCookie : public NPCFunction {
public:
	CNPC_DeleteDbCookie();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int DeleteDbCookie(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId);
};

