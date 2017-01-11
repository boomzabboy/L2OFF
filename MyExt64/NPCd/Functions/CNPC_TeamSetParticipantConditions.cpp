
#include <NPCd/Functions/CNPC_TeamSetParticipantConditions.h>
#include <Common/CLog.h>

CNPC_TeamSetParticipantConditions::CNPC_TeamSetParticipantConditions() :
	NPCFunction(L"TeamSetParticipantConditions", &TeamSetParticipantConditions)
{
}

void* CNPC_TeamSetParticipantConditions::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamSetParticipantConditions::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamSetParticipantConditions::TeamSetParticipantConditions(CNPC *npc, int eventId, int teamId, int conditionMask)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamSetParticipantConditions stub");
	return 0;
}

