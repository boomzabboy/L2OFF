
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_Remove : public NPCFunction {
public:
	CStrList_Remove();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Remove(CStrList *strList, wchar_t *value);
};

