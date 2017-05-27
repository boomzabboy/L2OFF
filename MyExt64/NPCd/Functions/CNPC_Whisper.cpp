
#include <NPCd/Functions/CNPC_Whisper.h>
#include <NPCd/NPCd.h>
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
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_STRING);
}

int CNPC_Whisper::Whisper(CNPC *npc, CSharedCreatureData *talker, wchar_t *str)
{
	NPCd::Send("chddS", 0x36, NPCd::WHISPER, npc->sm->index, talker->index, str);
	return 0;
}

