
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_SharedInstantZone_Close : public NPCFunction {
public:
	CNPC_SharedInstantZone_Close();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SharedInstantZone_Close(CNPC *npc, int inZoneTypeId);
};

