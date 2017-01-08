
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CIntList.h>


class CIntList_GetItemIndex : public NPCFunction {
public:
	CIntList_GetItemIndex();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetItemIndex(CIntList *intList, int value);
};

