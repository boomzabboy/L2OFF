
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SendNpcConfirmDlgAround : public NPCFunction {
public:
	CNPC_SendNpcConfirmDlgAround();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SendNpcConfirmDlgAround(CNPC *npc, int msgId, CSharedCreatureData *c, int range, int userLevelMin, int userLevelMax);
};

