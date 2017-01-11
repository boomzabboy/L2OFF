
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <NPCd/CIntList.h>

class CNPC_TeamEventAddMembersWithBalance : public NPCFunction {
public:
	CNPC_TeamEventAddMembersWithBalance();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int TeamEventAddMembersWithBalance(CNPC *npc, int eventId, CIntList *intList, int teamsNumber, int balanceCategoryFrom, int balanceCategoryTo);
};

