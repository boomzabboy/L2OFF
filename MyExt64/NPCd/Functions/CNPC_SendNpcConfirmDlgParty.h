
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SendNpcConfirmDlgParty : public NPCFunction {
public:
	CNPC_SendNpcConfirmDlgParty();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SendNpcConfirmDlgParty(CNPC *npc, int msgId, CSharedCreatureData *c);
};

