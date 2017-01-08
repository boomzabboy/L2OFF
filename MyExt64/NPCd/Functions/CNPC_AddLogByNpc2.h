
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_AddLogByNpc2 : public NPCFunction {
public:
	CNPC_AddLogByNpc2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int AddLogByNpc2(CNPC *npc, int logId, CSharedCreatureData *creature, wchar_t *str1, wchar_t *str2, INT64 param1, INT64 param2, INT64 param3, INT64 param4, INT64 param5, INT64 param6);
};

