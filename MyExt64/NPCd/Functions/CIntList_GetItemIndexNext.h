
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CIntList.h>

class CIntList_GetItemIndexNext : public NPCFunction {
public:
	CIntList_GetItemIndexNext();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetItemIndexNext(CIntList *intList, int value);
};

