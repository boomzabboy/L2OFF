
#include <NPCd/Functions/CIntList_RemoveAt.h>
#include <Common/CLog.h>

CIntList_RemoveAt::CIntList_RemoveAt() :
	NPCFunction(L"RemoveAt", &RemoveAt)
{
}

void* CIntList_RemoveAt::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CIntList_RemoveAt::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CIntList_RemoveAt::RemoveAt(CIntList *intList, int index)
{
    CLog::Add(CLog::Blue, L"CIntList::RemoveAt stub");
	return 0;
}

