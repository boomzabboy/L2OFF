
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_SetMaxSize : public NPCFunction {
public:
	CStrList_SetMaxSize();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetMaxSize(CStrList *strList, int maxSize);
};

