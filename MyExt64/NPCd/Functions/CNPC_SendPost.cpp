
#include <NPCd/Functions/CNPC_SendPost.h>
#include <Common/CLog.h>

CNPC_SendPost::CNPC_SendPost() :
	NPCFunction(L"SendPost", &SendPost)
{
}

void* CNPC_SendPost::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5], params[6], params[7], params[8], params[9], params[10], params[11], params[12], params[13], params[14], params[15], params[16], params[17], params[18], params[19], params[20], params[21]);
}

void CNPC_SendPost::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_STRING);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_SendPost::SendPost(CNPC *npc, int userDbId, wchar_t *title, wchar_t *msg, int tradeMoney, int itemId1, int itemAmount1, int itemId2, int itemAmount2, int itemId3, int itemAmount3, int itemId4, int itemAmount4, int itemId5, int itemAmount5, int itemId6, int itemAmount6, int itemId7, int itemAmount7, int itemId8, int itemAmount8, int itemId9, int itemAmount9)
{
    CLog::Add(CLog::Blue, L"CNPC::SendPost stub");
	return 0;
}

