
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_RegisterAsBirthdayManager : public NPCFunction {
public:
	CNPC_RegisterAsBirthdayManager();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int RegisterAsBirthdayManager(CNPC *npc);
};

