
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_GetItemIndexNext : public NPCFunction {
public:
	CStrList_GetItemIndexNext();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetItemIndexNext(CStrList *strList, wchar_t *value);
};

