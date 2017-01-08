
#include <NPCd/Functions/CNPC_Whisper.h>
#include <Common/CLog.h>

CNPC_Whisper::CNPC_Whisper() :
	NPCFunction(L"Whisper", &Whisper)
{
}

void* CNPC_Whisper::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_Whisper::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_STRING);
}

int CNPC_Whisper::Whisper(CNPC *npc, void *talker, const wchar_t *text)
{
	//CLog::Add(CLog::Blue, L"[npc @ %p] -> Whisper( [creature @ %p] , \"%s\" )", npc, talker, text);
	//return reinterpret_cast<int(*)(void*, const wchar_t*)>(0x49D8E8)(npc, text); // shouts the text instead
	CLog::Add(CLog::Blue, L"CNPC::Whisper stub");
	return 0;
}

