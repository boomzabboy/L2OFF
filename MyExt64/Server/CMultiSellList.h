
#pragma once

#include <Common/Utils.h>

class CMultiSellList {
public:
	static void Init();

	static void __cdecl SendListWrapper(CMultiSellList *self, class CUser *user, class CNPC *npc);

	void SendList(CUser *user, CNPC *npc);

	unsigned char padding0x0000[0x10];
	UINT32 id;
};

