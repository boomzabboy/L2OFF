
#include <NPCd/Functions/CNPC_GetDbData.h>
#include <Common/CLog.h>

CNPC_GetDbData::CNPC_GetDbData() :
	NPCFunction(L"GetDbData", &GetDbData)
{
}

void* CNPC_GetDbData::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9]);
}

void CNPC_GetDbData::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_GetDbData::GetDbData(CNPC *npc, wchar_t *str1, wchar_t *str2, wchar_t *str3, wchar_t *str4, wchar_t *str5, wchar_t *str6, wchar_t *str7, wchar_t *str8, wchar_t *str9, wchar_t *str10)
{
    CLog::Add(CLog::Blue, L"CNPC::GetDbData stub");
	return 0;
}

