
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_Dummy1 : public NPCFunction {
public:
	GlobalObject_Dummy1();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int Dummy1(void*);
};

