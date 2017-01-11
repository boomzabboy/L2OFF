
#include <NPCd/Functions/CNPC_TeamGetInactiveCharacters.h>
#include <Common/CLog.h>

CNPC_TeamGetInactiveCharacters::CNPC_TeamGetInactiveCharacters() :
	NPCFunction(L"TeamGetInactiveCharacters", &TeamGetInactiveCharacters)
{
}

void* CNPC_TeamGetInactiveCharacters::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamGetInactiveCharacters::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamGetInactiveCharacters::TeamGetInactiveCharacters(CNPC *npc, int eventId, int teamId, int inactiveTimeSec)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamGetInactiveCharacters stub");
	return 0;
}

