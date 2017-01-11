
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>

class CNPC_GlobalAnnounce : public NPCFunction {
public:
	CNPC_GlobalAnnounce();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GlobalAnnounce(CNPC *npc, int announceType, wchar_t *announceMessage);
};

