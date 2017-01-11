
#include <NPCd/Functions/CStrList_SetMaxSize.h>
#include <Common/CLog.h>

CStrList_SetMaxSize::CStrList_SetMaxSize() :
	NPCFunction(L"SetMaxSize", &SetMaxSize)
{
}

void* CStrList_SetMaxSize::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_SetMaxSize::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CStrList_SetMaxSize::SetMaxSize(CStrList *strList, int maxSize)
{
    CLog::Add(CLog::Blue, L"CStrList::SetMaxSize stub");
	return 0;
}

