
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_GetItemIndex : public NPCFunction {
public:
	CStrList_GetItemIndex();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetItemIndex(CStrList *strList, wchar_t *value);
};

