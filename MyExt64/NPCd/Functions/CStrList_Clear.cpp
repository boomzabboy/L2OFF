
#include <NPCd/Functions/CStrList_Clear.h>
#include <Common/CLog.h>

CStrList_Clear::CStrList_Clear() :
	NPCFunction(L"Clear", &Clear)
{
}

void* CStrList_Clear::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*)>(functionPtr.functionPtr)(
		caller);
}

void CStrList_Clear::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);

}

int CStrList_Clear::Clear(CStrList *strList)
{
    CLog::Add(CLog::Blue, L"CStrList::Clear stub");
	return 0;
}

