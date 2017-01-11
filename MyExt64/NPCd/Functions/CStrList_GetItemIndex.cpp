
#include <NPCd/Functions/CStrList_GetItemIndex.h>
#include <Common/CLog.h>

CStrList_GetItemIndex::CStrList_GetItemIndex() :
	NPCFunction(L"GetItemIndex", &GetItemIndex)
{
}

void* CStrList_GetItemIndex::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_GetItemIndex::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CStrList_GetItemIndex::GetItemIndex(CStrList *strList, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CStrList::GetItemIndex stub");
	return 0;
}

