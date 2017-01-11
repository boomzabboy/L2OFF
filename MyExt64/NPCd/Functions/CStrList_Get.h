
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_Get : public NPCFunction {
public:
	CStrList_Get();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Get(CStrList *strList, int index);
};

