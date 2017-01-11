
#include <NPCd/Functions/CStrList_Remove.h>
#include <Common/CLog.h>

CStrList_Remove::CStrList_Remove() :
	NPCFunction(L"Remove", &Remove)
{
}

void* CStrList_Remove::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_Remove::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_STRING);
}

int CStrList_Remove::Remove(CStrList *strList, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CStrList::Remove stub");
	return 0;
}

