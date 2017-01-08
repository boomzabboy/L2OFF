
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ShowOlympiadMatchList : public NPCFunction {
public:
	CNPC_ShowOlympiadMatchList();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ShowOlympiadMatchList(CNPC *npc, CSharedCreatureData *creature);
};

