
#include <NPCd/Functions/CStrList_Get.h>
#include <Common/CLog.h>

CStrList_Get::CStrList_Get() :
	NPCFunction(L"Get", &Get)
{
}

void* CStrList_Get::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CStrList_Get::SetTypes()
{
	SetReturnType(Type::TYPE_STRING);
	AddParameter(Type::TYPE_INT);
}

int CStrList_Get::Get(CStrList *strList, int index)
{
    CLog::Add(CLog::Blue, L"CStrList::Get stub");
	return 0;
}

