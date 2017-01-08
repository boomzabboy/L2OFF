
#include <NPCd/Functions/GlobalObject_ShowOnScreenNpcStringMsg.h>
#include <Common/CLog.h>

GlobalObject_ShowOnScreenNpcStringMsg::GlobalObject_ShowOnScreenNpcStringMsg() :
	NPCFunction(L"ShowOnScreenNpcStringMsg", &ShowOnScreenNpcStringMsg)
{
}

void* GlobalObject_ShowOnScreenNpcStringMsg::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15]);
}

void GlobalObject_ShowOnScreenNpcStringMsg::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_INT);
	AddParameter(TYPE_STRING);
	AddParameter(TYPE_STRING);
	AddParameter(TYPE_STRING);
	AddParameter(TYPE_STRING);
	AddParameter(TYPE_STRING);
}

int GlobalObject_ShowOnScreenNpcStringMsg::ShowOnScreenNpcStringMsg(void*, int range, int msgPosType, int param1, int fontSize, int param2, int param3, int effect, int time, int fade, int npcStringId, wchar_t *str1, wchar_t *str2, wchar_t *str3, wchar_t *str4, wchar_t *str5)
{
    CLog::Add(CLog::Blue, L"GlobalObject::ShowOnScreenNpcStringMsg stub");
	return 0;
}

