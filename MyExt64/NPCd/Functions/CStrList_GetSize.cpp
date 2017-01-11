
#include <NPCd/Functions/CStrList_GetSize.h>
#include <Common/CLog.h>

CStrList_GetSize::CStrList_GetSize() :
	NPCFunction(L"GetSize", &GetSize)
{
}

void* CStrList_GetSize::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*)>(functionPtr.functionPtr)(
		caller);
}

void CStrList_GetSize::SetTypes()
{
	SetReturnType(Type::TYPE_INT);

}

int CStrList_GetSize::GetSize(CStrList *strList)
{
    CLog::Add(CLog::Blue, L"CStrList::GetSize stub");
	return 0;
}

