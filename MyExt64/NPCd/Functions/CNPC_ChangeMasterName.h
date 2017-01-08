
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ChangeMasterName : public NPCFunction {
public:
	CNPC_ChangeMasterName();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeMasterName(CNPC *npc, CSharedCreatureData *talker, wchar_t *name);
};

