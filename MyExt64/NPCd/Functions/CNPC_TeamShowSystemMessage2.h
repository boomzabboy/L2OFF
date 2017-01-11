
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_TeamShowSystemMessage2 : public NPCFunction {
public:
	CNPC_TeamShowSystemMessage2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamShowSystemMessage2(CNPC *npc, int eventId, int teamId, int sysMsgNo, int paramCount, wchar_t *param1, wchar_t *param2, wchar_t *param3, wchar_t *param4, wchar_t *param5, wchar_t *param6, wchar_t *param7);
};

