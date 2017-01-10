
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_ShowOnScreenNpcStringMsg : public NPCFunction {
public:
	GlobalObject_ShowOnScreenNpcStringMsg();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int ShowOnScreenNpcStringMsg(void*, int msgPosType, int param1, int fontSize, int param2, int param3, int effect, int time, int fade, int npcStringId, wchar_t *str1, wchar_t *str2, wchar_t *str3, wchar_t *str4, wchar_t *str5);
};

