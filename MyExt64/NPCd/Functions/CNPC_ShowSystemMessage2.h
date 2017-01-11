
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ShowSystemMessage2 : public NPCFunction {
public:
	CNPC_ShowSystemMessage2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ShowSystemMessage2(CNPC *npc, CSharedCreatureData *target, int sysMsgNo, int paramCount, wchar_t *param1, wchar_t *param2, wchar_t *param3, wchar_t *param4, wchar_t *param5, wchar_t *param6, wchar_t *param7, wchar_t *param8);
};

