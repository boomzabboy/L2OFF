
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_Dummy2 : public NPCFunction {
public:
	GlobalObject_Dummy2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Dummy2(void*);
};

