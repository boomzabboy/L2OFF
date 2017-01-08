
#pragma once

#include <NPCd/NPCFunction.h>
#include <Common/CSharedCreatureData.h>

class GlobalObject_OwnItemCountEx2 : public NPCFunction {
public:
	GlobalObject_OwnItemCountEx2();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int OwnItemCountEx2(void*, CSharedCreatureData *creature, int itemClassId, int enchantLevel, int findAugment);
};

