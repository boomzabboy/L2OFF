
#include <NPCd/Functions/GlobalObject_OwnItemCount2.h>
#include <Common/CLog.h>

GlobalObject_OwnItemCount2::GlobalObject_OwnItemCount2() :
	NPCFunction(L"OwnItemCount2", &OwnItemCount2)
{
}

void* GlobalObject_OwnItemCount2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void GlobalObject_OwnItemCount2::SetTypes()
{
	SetReturnType(TYPE_INT);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
}

int GlobalObject_OwnItemCount2::OwnItemCount2(void*, CSharedCreatureData *creature, int itemClassId, int findAugment)
{
    CLog::Add(CLog::Blue, L"GlobalObject::OwnItemCount2 stub");
	return 0;
}

