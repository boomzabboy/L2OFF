
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_BroadCastUIEventNpcStr : public NPCFunction {
public:
	GlobalObject_BroadCastUIEventNpcStr();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int BroadCastUIEventNpcStr(void*, CSharedCreatureData *c, int range, int showTimer, int unk1, int unk2, wchar_t *timerType, wchar_t *startTimeMin, wchar_t *startTimeSec, int npcStringId, wchar_t *endTimeMin, wchar_t *endTimeSec);
};

