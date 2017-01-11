
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_GetSize : public NPCFunction {
public:
	CStrList_GetSize();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int GetSize(CStrList *strList);
};

