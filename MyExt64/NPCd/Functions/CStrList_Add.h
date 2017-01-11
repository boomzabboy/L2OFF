
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_Add : public NPCFunction {
public:
	CStrList_Add();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Add(CStrList *strList, wchar_t *value);
};

