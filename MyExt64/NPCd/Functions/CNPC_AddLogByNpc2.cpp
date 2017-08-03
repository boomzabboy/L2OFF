
#include <NPCd/Functions/CNPC_AddLogByNpc2.h>
#include <Common/CLog.h>

CNPC_AddLogByNpc2::CNPC_AddLogByNpc2() :
	NPCFunction(L"AddLogByNpc2", &AddLogByNpc2)
{
}

void* CNPC_AddLogByNpc2::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
}

void CNPC_AddLogByNpc2::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_INT64);
	AddParameter(Type::TYPE_INT64);
	AddParameter(Type::TYPE_INT64);
	AddParameter(Type::TYPE_INT64);
	AddParameter(Type::TYPE_INT64);
	AddParameter(Type::TYPE_INT64);
}

int CNPC_AddLogByNpc2::AddLogByNpc2(CNPC *npc, int logId, CSharedCreatureData *creature, wchar_t *str1, wchar_t *str2, __int64 param1, __int64 param2, __int64 param3, __int64 param4, __int64 param5, __int64 param6)
{
	reinterpret_cast<void(*)(UINT64, int, const wchar_t*, ...)>(0x4780E0)(
		0x291EF90, 6, L"%I64d,%I64d,,,,%I64d,%I64d,%I64d,,,,%I64d,%I64d,%I64d,%I64d,%I64d,%I64d,,,,,%s,%s,,,",
			logId, creature->dbId,
			static_cast<INT64>(creature->x), static_cast<INT64>(creature->y), static_cast<INT64>(creature->z),
			param1, param2, param3, param4, param5, param6, str1, str2);
	return 0;
}

