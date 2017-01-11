
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_SendUIEventNpcStr : public NPCFunction {
public:
	GlobalObject_SendUIEventNpcStr();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SendUIEventNpcStr(void*, CSharedCreatureData *c, int showTimer, int unk1, int unk2, wchar_t *timerType, wchar_t *startTimeMin, wchar_t *startTimeSec, int npcStringId, wchar_t *endTimeMin, wchar_t *endTimeSec);
};

