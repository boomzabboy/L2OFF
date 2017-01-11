
#include <NPCd/Functions/CNPC_TeamEventSetParticipantConditions.h>
#include <Common/CLog.h>

CNPC_TeamEventSetParticipantConditions::CNPC_TeamEventSetParticipantConditions() :
	NPCFunction(L"TeamEventSetParticipantConditions", &TeamEventSetParticipantConditions)
{
}

void* CNPC_TeamEventSetParticipantConditions::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeamEventSetParticipantConditions::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamEventSetParticipantConditions::TeamEventSetParticipantConditions(CNPC *npc, int eventId, int conditionMask)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamEventSetParticipantConditions stub");
	return 0;
}

