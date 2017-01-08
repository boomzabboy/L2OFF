
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_OwnItemCount2 : public NPCFunction {
public:
	GlobalObject_OwnItemCount2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int OwnItemCount2(void*, CSharedCreatureData *creature, int itemClassId, int findAugment);
};

