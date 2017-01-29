
#include <NPCd/Functions/GlobalObject_DebugLog.h>
#include <Common/CLog.h>

GlobalObject_DebugLog::GlobalObject_DebugLog() :
	NPCFunction(L"DebugLog", &DebugLog)
{
}

void* GlobalObject_DebugLog::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5]);
}

void GlobalObject_DebugLog::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int GlobalObject_DebugLog::DebugLog(void*, const wchar_t *s1, const wchar_t *s2, const wchar_t *s3, const int i1, const int i2, const int i3)
{
	CLog::Add(CLog::Blue, L"DebugLog: s1=%s s2=%s s3=%s i1=%d i2=%d i3=%d", s1, s2, s3, i1, i2, i3);
	return 0;
}

