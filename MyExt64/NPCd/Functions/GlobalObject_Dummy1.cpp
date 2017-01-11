
#include <NPCd/Functions/GlobalObject_Dummy1.h>
#include <Common/CLog.h>

GlobalObject_Dummy1::GlobalObject_Dummy1() :
	NPCFunction(L"Dummy1", &Dummy1)
{
}

void* GlobalObject_Dummy1::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*)>(functionPtr.functionPtr)(
		caller);
}

void GlobalObject_Dummy1::SetTypes()
{
	SetReturnType(Type::TYPE_INT64);
}

int GlobalObject_Dummy1::Dummy1(void*)
{
    CLog::Add(CLog::Blue, L"GlobalObject::Dummy1 stub");
	return 0;
}

