
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_DebugLog : public NPCFunction {
public:
	GlobalObject_DebugLog();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int DebugLog(void*, const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const int i1, const int i2, const int i3);
};

