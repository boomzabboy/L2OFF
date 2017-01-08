
#include <NPCd/Functions/CIntList_SetMaxSize.h>
#include <Common/CLog.h>

CIntList_SetMaxSize::CIntList_SetMaxSize() :
	NPCFunction(L"SetMaxSize", &SetMaxSize)
{
}

void* CIntList_SetMaxSize::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CIntList_SetMaxSize::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_INT);
}

int CIntList_SetMaxSize::SetMaxSize(CIntList *intList, int maxSize)
{
    CLog::Add(CLog::Blue, L"CIntList::SetMaxSize stub");
	return 0;
}

