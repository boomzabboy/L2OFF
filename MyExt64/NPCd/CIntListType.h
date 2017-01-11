
#pragma once

#include <NPCd/Type.h>

class CIntListType : public Type {
public:
	virtual void* Factory();

	virtual bool IsClass();

	static void RegisterVariable(void *registry, const wchar_t *name, size_t offset, class CIntList *data);
};

