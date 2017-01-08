
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_ChangeNickName : public NPCFunction {
public:
	CNPC_ChangeNickName();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ChangeNickName(CNPC *npc, CSharedCreatureData *creature, wchar_t *name);
};

