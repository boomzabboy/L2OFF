
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_IsToggleSkillOnOff : public NPCFunction {
public:
	CNPC_IsToggleSkillOnOff();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int IsToggleSkillOnOff(CNPC *npc, CSharedCreatureData *target, int skillUid);
};

