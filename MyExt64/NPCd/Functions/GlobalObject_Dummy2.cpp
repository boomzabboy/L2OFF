
#include <NPCd/Functions/GlobalObject_Dummy2.h>
#include <Common/CLog.h>

GlobalObject_Dummy2::GlobalObject_Dummy2() :
	NPCFunction(L"Dummy2", &Dummy2)
{
}

void* GlobalObject_Dummy2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*)>(functionPtr.functionPtr)(
		caller);
}

void GlobalObject_Dummy2::SetTypes()
{
	SetReturnType(Type::TYPE_INT64);
}

int GlobalObject_Dummy2::Dummy2(void*)
{
    CLog::Add(CLog::Blue, L"GlobalObject::Dummy2 stub");
	return 0;
}

