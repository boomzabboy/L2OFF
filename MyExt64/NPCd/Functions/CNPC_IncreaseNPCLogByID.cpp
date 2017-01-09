
#include <NPCd/Functions/CNPC_IncreaseNPCLogByID.h>
#include <Common/CLog.h>

CNPC_IncreaseNPCLogByID::CNPC_IncreaseNPCLogByID() :
	NPCFunction(L"IncreaseNPCLogByID", &IncreaseNPCLogByID)
{
}

void* CNPC_IncreaseNPCLogByID::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4]);
}

void CNPC_IncreaseNPCLogByID::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_IncreaseNPCLogByID::IncreaseNPCLogByID(CNPC *npc, CSharedCreatureData *talker, int questId, int questState, int npcId, int maxValue)
{
    CLog::Add(CLog::Blue, L"CNPC::IncreaseNPCLogByID stub");
	return 0;
}

