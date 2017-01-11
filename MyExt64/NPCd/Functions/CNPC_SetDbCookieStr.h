
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SetDbCookieStr : public NPCFunction {
public:
	CNPC_SetDbCookieStr();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetDbCookieStr(CNPC *npc, CSharedCreatureData *c, int groupId, int cookieId, wchar_t *value);
};

