
#include <NPCd/CStrListType.h>
#include <NPCd/CStrList.h>
#include <NPCd/Variable.h>

void* CStrListType::Factory()
{
	CStrList *ret = new CStrList();
	ret->RegisterFunctions(reinterpret_cast<void*>(this));
	ret->RegisterVariables(reinterpret_cast<void*>(this));
	return reinterpret_cast<void*>(ret);
}

bool CStrListType::IsClass()
{
	return true;
}

void CStrListType::RegisterVariable(void *registry, const wchar_t *name, size_t offset, CStrList *data)
{
	Variable *v = new Variable();
	v->name = name;
	v->offset = offset;
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	v->type = *reinterpret_cast<Type**(*)(void*, Type::TypeID)>(0x422E0C)(
		ptr, Type::TYPE_STRLIST);
	reinterpret_cast<void(*)(void*, Variable*)>(0x574FC0)(registry, v);
}

CompileTimeOffsetCheck(CStrListType, padding0x0038, 0x38);

