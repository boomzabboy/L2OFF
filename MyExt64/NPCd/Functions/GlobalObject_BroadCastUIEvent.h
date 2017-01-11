
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_BroadCastUIEvent : public NPCFunction {
public:
	GlobalObject_BroadCastUIEvent();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int BroadCastUIEvent(void*, CSharedCreatureData *c, int range, int showTimer, int unk1, int unk2, wchar_t *timerType, wchar_t *startTimeMin, wchar_t *startTimeSec, wchar_t *timerText, wchar_t *endTimeMin, wchar_t *endTimeSec);
};

