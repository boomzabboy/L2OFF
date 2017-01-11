
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CIntList.h>

class CIntList_RemoveAt : public NPCFunction {
public:
	CIntList_RemoveAt();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int RemoveAt(CIntList *intList, int index);
};

