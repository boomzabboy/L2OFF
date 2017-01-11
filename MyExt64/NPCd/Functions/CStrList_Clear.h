
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CStrList.h>

class CStrList_Clear : public NPCFunction {
public:
	CStrList_Clear();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Clear(CStrList *strList);
};

