
#pragma once

#include <NPCd/Type.h>

class CreatureData2Type : public Type {
public:
	virtual void* Factory();

	virtual bool IsClass();

	static void RegisterVariable(void *registry, const wchar_t *name, size_t offset, class CreatureData2 *data);
};

