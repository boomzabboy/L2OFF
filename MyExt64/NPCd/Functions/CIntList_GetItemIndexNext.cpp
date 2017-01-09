
#include <NPCd/Functions/CIntList_GetItemIndexNext.h>
#include <Common/CLog.h>

CIntList_GetItemIndexNext::CIntList_GetItemIndexNext() :
	NPCFunction(L"GetItemIndexNext", &GetItemIndexNext)
{
}

void* CIntList_GetItemIndexNext::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CIntList_GetItemIndexNext::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CIntList_GetItemIndexNext::GetItemIndexNext(CIntList *intList, int value)
{
    CLog::Add(CLog::Blue, L"CIntList::GetItemIndexNext stub");
	return 0;
}

