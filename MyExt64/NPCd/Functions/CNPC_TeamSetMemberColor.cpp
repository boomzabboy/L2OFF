
#include <NPCd/Functions/CNPC_TeamSetMemberColor.h>
#include <Common/CLog.h>

CNPC_TeamSetMemberColor::CNPC_TeamSetMemberColor() :
	NPCFunction(L"TeamSetMemberColor", &TeamSetMemberColor)
{
}

void* CNPC_TeamSetMemberColor::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_TeamSetMemberColor::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
}

int CNPC_TeamSetMemberColor::TeamSetMemberColor(CNPC *npc, CSharedCreatureData *target, int color)
{
    CLog::Add(CLog::Blue, L"CNPC::TeamSetMemberColor stub");
	return 0;
}

