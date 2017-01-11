
#include <NPCd/Functions/CNPC_TeamInstantTeleport.h>
#include <Common/CLog.h>

CNPC_TeamInstantTeleport::CNPC_TeamInstantTeleport() :
	NPCFunction(L"TeamInstantTeleport", &TeamInstantTeleport)
{
}

void* CNPC_TeamInstantTeleport::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_TeamInstantTeleport::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamInstantTeleport::TeamInstantTeleport(CNPC *npc, int eventId, int teamId, int x, int y, int z)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamInstantTeleport stub");
	return 0;
}

