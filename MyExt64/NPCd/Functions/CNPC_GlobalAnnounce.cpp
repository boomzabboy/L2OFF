
#include <NPCd/Functions/CNPC_GlobalAnnounce.h>
#include <Common/CLog.h>

CNPC_GlobalAnnounce::CNPC_GlobalAnnounce() :
	NPCFunction(L"GlobalAnnounce", &GlobalAnnounce)
{
}

void* CNPC_GlobalAnnounce::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_GlobalAnnounce::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_GlobalAnnounce::GlobalAnnounce(CNPC *npc, wchar_t *message)
{
    CLog::Add(CLog::Blue, L"CNPC::GlobalAnnounce stub");
	return 0;
}

