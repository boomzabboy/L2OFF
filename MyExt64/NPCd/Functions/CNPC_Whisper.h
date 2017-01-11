
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>
#include <Common/CSharedCreatureData.h>

class CNPC_Whisper : public NPCFunction {
public:
	CNPC_Whisper();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Whisper(CNPC *npc, CSharedCreatureData *talker, wchar_t *str);
};

