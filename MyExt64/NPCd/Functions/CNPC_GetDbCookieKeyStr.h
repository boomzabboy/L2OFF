
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_GetDbCookieKeyStr : public NPCFunction {
public:
	CNPC_GetDbCookieKeyStr();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetDbCookieKeyStr(CNPC *npc, CSharedCreatureData *c, int groupId, wchar_t *value);
};

