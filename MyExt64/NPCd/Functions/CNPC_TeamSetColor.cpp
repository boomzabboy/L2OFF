
#include <NPCd/Functions/CNPC_TeamSetColor.h>
#include <Common/CLog.h>

CNPC_TeamSetColor::CNPC_TeamSetColor() :
	NPCFunction(L"TeamSetColor", &TeamSetColor)
{
}

void* CNPC_TeamSetColor::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_TeamSetColor::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamSetColor::TeamSetColor(CNPC *npc, int eventId, int teamId, int color)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamSetColor stub");
	return 0;
}

