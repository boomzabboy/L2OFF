
#include <NPCd/Functions/CStrList_RemoveAt.h>
#include <Common/CLog.h>

CStrList_RemoveAt::CStrList_RemoveAt() :
	NPCFunction(L"RemoveAt", &RemoveAt)
{
}

void* CStrList_RemoveAt::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_RemoveAt::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CStrList_RemoveAt::RemoveAt(CStrList *strList, int index)
{
    CLog::Add(CLog::Blue, L"CStrList::RemoveAt stub");
	return 0;
}

