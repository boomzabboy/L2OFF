
#include <NPCd/Functions/CStrList_GetItemIndexNext.h>
#include <Common/CLog.h>

CStrList_GetItemIndexNext::CStrList_GetItemIndexNext() :
	NPCFunction(L"GetItemIndexNext", &GetItemIndexNext)
{
}

void* CStrList_GetItemIndexNext::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_GetItemIndexNext::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CStrList_GetItemIndexNext::GetItemIndexNext(CStrList *strList, wchar_t *value)
{
    CLog::Add(CLog::Blue, L"CStrList::GetItemIndexNext stub");
	return 0;
}

