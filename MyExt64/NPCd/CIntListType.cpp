
#include <NPCd/CIntListType.h>
#include <NPCd/CIntList.h>
#include <NPCd/Variable.h>

void* CIntListType::Factory()
{
	CIntList *ret = new CIntList();
	ret->RegisterFunctions(reinterpret_cast<void*>(this));
	ret->RegisterVariables(reinterpret_cast<void*>(this));
	return reinterpret_cast<void*>(ret);
}

bool CIntListType::IsClass()
{
	return true;
}

void CIntListType::RegisterVariable(void *registry, const wchar_t *name, size_t offset, CIntList *data)
{
	Variable *v = new Variable();
	v->name = name;
	v->offset = offset;
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	v->type = *reinterpret_cast<Type**(*)(void*, Type::TypeID)>(0x422E0C)(
		ptr, Type::TYPE_INTLIST);
	reinterpret_cast<void(*)(void*, Variable*)>(0x574FC0)(registry, v);
}

CompileTimeOffsetCheck(CIntListType, padding0x0038, 0x38);

