
#include <NPCd/Functions/CNPC_TeamInstantTeleportWithConditions.h>
#include <Common/CLog.h>

CNPC_TeamInstantTeleportWithConditions::CNPC_TeamInstantTeleportWithConditions() :
	NPCFunction(L"TeamInstantTeleportWithConditions", &TeamInstantTeleportWithConditions)
{
}

void* CNPC_TeamInstantTeleportWithConditions::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5]);
}

void CNPC_TeamInstantTeleportWithConditions::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamInstantTeleportWithConditions::TeamInstantTeleportWithConditions(CNPC *npc, int eventId, int teamId, int x, int y, int z, int kickInvalid)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamInstantTeleportWithConditions stub");
	return 0;
}

