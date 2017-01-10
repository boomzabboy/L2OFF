
#include <NPCd/Functions/GlobalObject_OwnItemCountEx2.h>
#include <Common/CLog.h>

GlobalObject_OwnItemCountEx2::GlobalObject_OwnItemCountEx2() :
	NPCFunction(L"OwnItemCountEx2", &OwnItemCountEx2)
{
}

void* GlobalObject_OwnItemCountEx2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3]);
}

void GlobalObject_OwnItemCountEx2::SetTypes()
{
	SetReturnType(Type::TYPE_INT64);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int GlobalObject_OwnItemCountEx2::OwnItemCountEx2(void*, CSharedCreatureData *creature, int itemClassId, int enchantLevel, int findAugment)
{
    CLog::Add(CLog::Blue, L"GlobalObject::OwnItemCountEx2 stub");
	return 0;
}

