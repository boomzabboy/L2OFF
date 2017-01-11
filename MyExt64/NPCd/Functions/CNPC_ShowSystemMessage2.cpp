
#include <NPCd/Functions/CNPC_ShowSystemMessage2.h>
#include <Common/CLog.h>

CNPC_ShowSystemMessage2::CNPC_ShowSystemMessage2() :
	NPCFunction(L"ShowSystemMessage2", &ShowSystemMessage2)
{
}

void* CNPC_ShowSystemMessage2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10]);
}

void CNPC_ShowSystemMessage2::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_ShowSystemMessage2::ShowSystemMessage2(CNPC *npc, CSharedCreatureData *target, int sysMsgNo, int paramCount, wchar_t *param1, wchar_t *param2, wchar_t *param3, wchar_t *param4, wchar_t *param5, wchar_t *param6, wchar_t *param7, wchar_t *param8)
{
    CLog::Add(CLog::Blue, L"CNPC::ShowSystemMessage2 stub");
	return 0;
}

