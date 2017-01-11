
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_DelDbDataById : public NPCFunction {
public:
	CNPC_DelDbDataById();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int DelDbDataById(CNPC *npc, int id);
};

