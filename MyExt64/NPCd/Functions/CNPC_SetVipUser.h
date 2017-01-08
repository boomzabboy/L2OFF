
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SetVipUser : public NPCFunction {
public:
	CNPC_SetVipUser();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetVipUser(CNPC *npc, CSharedCreatureData *talker, int duration, int param1, int param2, wchar_t *param3);
};

