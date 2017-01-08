
#include <NPCd/Functions/CIntList_GetItemIndex.h>
#include <Common/CLog.h>

CIntList_GetItemIndex::CIntList_GetItemIndex() :
	NPCFunction(L"GetItemIndex", &GetItemIndex)
{
}

void* CIntList_GetItemIndex::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CIntList_GetItemIndex::SetTypes()
{
	SetReturnType(TYPE_INT);
	AddParameter(TYPE_INT);
}

int CIntList_GetItemIndex::GetItemIndex(CIntList *intList, int value)
{
    CLog::Add(CLog::Blue, L"CIntList::GetItemIndex stub");
	return 0;
}

