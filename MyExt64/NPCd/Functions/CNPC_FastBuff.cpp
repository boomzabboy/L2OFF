
#include <NPCd/Functions/CNPC_FastBuff.h>
#include <Common/CLog.h>

CNPC_FastBuff::CNPC_FastBuff() :
	NPCFunction(L"FastBuff", &FastBuff)
{
}

void* CNPC_FastBuff::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2]);
}

void CNPC_FastBuff::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_FastBuff::FastBuff(CNPC *npc, int index, int skillID, int skillLevel)
{
    CLog::Add(CLog::Blue, L"CNPC::FastBuff stub");
	return 0;
}

