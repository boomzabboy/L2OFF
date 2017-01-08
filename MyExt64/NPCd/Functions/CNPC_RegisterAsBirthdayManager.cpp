
#include <NPCd/Functions/CNPC_RegisterAsBirthdayManager.h>
#include <Common/CLog.h>

CNPC_RegisterAsBirthdayManager::CNPC_RegisterAsBirthdayManager() :
	NPCFunction(L"RegisterAsBirthdayManager", &RegisterAsBirthdayManager)
{
}

void* CNPC_RegisterAsBirthdayManager::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*)>(functionPtr.functionPtr)(
		caller);
}

void CNPC_RegisterAsBirthdayManager::SetTypes()
{
	SetReturnType(TYPE_VOID);

}

int CNPC_RegisterAsBirthdayManager::RegisterAsBirthdayManager(CNPC *npc)
{
    CLog::Add(CLog::Blue, L"CNPC::RegisterAsBirthdayManager stub");
	return 0;
}

