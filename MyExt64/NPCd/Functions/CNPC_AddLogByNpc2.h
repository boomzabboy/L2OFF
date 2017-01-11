
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_AddLogByNpc2 : public NPCFunction {
public:
	CNPC_AddLogByNpc2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int AddLogByNpc2(CNPC *npc, int logId, CSharedCreatureData *creature, wchar_t *str1, wchar_t *str2, __int64 param1, __int64 param2, __int64 param3, __int64 param4, __int64 param5, __int64 param6);
};

