
#include <NPCd/Functions/CNPC_TeamSetRestartPoint.h>
#include <Common/CLog.h>

CNPC_TeamSetRestartPoint::CNPC_TeamSetRestartPoint() :
	NPCFunction(L"TeamSetRestartPoint", &TeamSetRestartPoint)
{
}

void* CNPC_TeamSetRestartPoint::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_TeamSetRestartPoint::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamSetRestartPoint::TeamSetRestartPoint(CNPC *npc, int eventId, int teamId, int x, int y, int z)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamSetRestartPoint stub");
	return 0;
}

