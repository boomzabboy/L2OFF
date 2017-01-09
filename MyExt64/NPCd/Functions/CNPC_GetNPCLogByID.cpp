
#include <NPCd/Functions/CNPC_GetNPCLogByID.h>
#include <Common/CLog.h>

CNPC_GetNPCLogByID::CNPC_GetNPCLogByID() :
	NPCFunction(L"GetNPCLogByID", &GetNPCLogByID)
{
}

void* CNPC_GetNPCLogByID::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3]);
}

void CNPC_GetNPCLogByID::SetTypes()
{
	SetReturnType(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_GetNPCLogByID::GetNPCLogByID(CNPC *npc, CSharedCreatureData *talker, int questId, int questState, int npcId)
{
    CLog::Add(CLog::Blue, L"CNPC::GetNPCLogByID stub");
	return 0;
}

