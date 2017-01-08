
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_IsVipUser : public NPCFunction {
public:
	CNPC_IsVipUser();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int IsVipUser(CNPC *npc, CSharedCreatureData *talker);
};

