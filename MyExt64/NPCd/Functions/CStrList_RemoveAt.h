
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_RemoveAt : public NPCFunction {
public:
	CStrList_RemoveAt();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int RemoveAt(CStrList *strList, int index);
};

