
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CIntList.h>


class CIntList_SetMaxSize : public NPCFunction {
public:
	CIntList_SetMaxSize();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SetMaxSize(CIntList *intList, int maxSize);
};

