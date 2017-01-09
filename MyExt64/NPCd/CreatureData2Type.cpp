
#include <NPCd/CreatureData2Type.h>
#include <NPCd/CreatureData2.h>
#include <NPCd/Variable.h>

void* CreatureData2Type::Factory()
{
	CreatureData2 *ret = new CreatureData2();
	ret->RegisterFunctions(reinterpret_cast<void*>(this));
	ret->RegisterVariables(reinterpret_cast<void*>(this));
	return reinterpret_cast<void*>(ret);
}

bool CreatureData2Type::IsClass()
{
	return true;
}

void CreatureData2Type::RegisterVariable(void *registry, const wchar_t *name, size_t offset, CreatureData2 *data)
{
	Variable *v = new Variable();
	v->name = name;
	v->offset = offset;
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	v->type = *reinterpret_cast<Type**(*)(void*, Type::TypeID)>(0x422E0C)(
		ptr, Type::TYPE_CREATURE2);
	reinterpret_cast<void(*)(void*, Variable*)>(0x574FC0)(registry, v);
}

CompileTimeOffsetCheck(CreatureData2Type, padding0x0038, 0x38);

