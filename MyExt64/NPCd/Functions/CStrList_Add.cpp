
#include <NPCd/Functions/CStrList_Add.h>
#include <Common/CLog.h>

CStrList_Add::CStrList_Add() :
	NPCFunction(L"Add", &Add)
{
}

void* CStrList_Add::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_Add::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_STRING);
}

int CStrList_Add::Add(CStrList *strList, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CStrList::Add stub");
	return 0;
}

