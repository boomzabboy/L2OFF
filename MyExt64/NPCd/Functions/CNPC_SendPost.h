
#pragma once

#include <NPCd/NPCFunction.h>
#include <NPCd/CNPC.h>


class CNPC_SendPost : public NPCFunction {
public:
	CNPC_SendPost();
	virtual void* Call(void *caller, void **params);
	virtual void SetTypes();
	static int SendPost(CNPC *npc, int userDbId, wchar_t *title, wchar_t *message, int tradeMoney, int itemId1, int itemAmount1, int itemId2, int itemAmount2, int itemId3, int itemAmount3, int itemId4, int itemAmount4, int itemId5, int itemAmount5, int itemId6, int itemAmount6, int itemId7, int itemAmount7, int itemId8, int itemAmount8, int itemId9, int itemAmount9);
};

