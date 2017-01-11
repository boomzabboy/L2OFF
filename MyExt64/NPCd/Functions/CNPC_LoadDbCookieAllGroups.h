
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_LoadDbCookieAllGroups : public NPCFunction {
public:
	CNPC_LoadDbCookieAllGroups();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int LoadDbCookieAllGroups(CNPC *npc, CSharedCreatureData *c);
};

