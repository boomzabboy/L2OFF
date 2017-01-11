
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_RegisterNpcConfirmDlg : public NPCFunction {
public:
	CNPC_RegisterNpcConfirmDlg();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int RegisterNpcConfirmDlg(CNPC *npc, int msgId);
};

