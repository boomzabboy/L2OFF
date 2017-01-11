
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_SharedInstantZone_Enter : public NPCFunction {
public:
	CNPC_SharedInstantZone_Enter();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SharedInstantZone_Enter(CNPC *npc, CSharedCreatureData *c, int inZoneTypeId, int enterType, int x, int y, int z);
};

