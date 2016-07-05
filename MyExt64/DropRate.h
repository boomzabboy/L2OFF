
#pragma once

#include <windows.h>
#include <vector>

class DropRate {
public:
	class ItemDrop {
	public:
		UINT32 itemId;
		UINT32 countMin;
		UINT32 countMax;
		double chance;
	};

	class ItemDropMulti {
	public:
		std::vector<ItemDrop*> *items;
		double chance;
	};

	static void Init();

	static void CNPCSetDrop(class CCreature *npc, UINT32 type, std::vector<ItemDrop*> &data);
	static void CNPCSetDropMulti(class CCreature *npc, UINT32 type, std::vector<ItemDropMulti*> &data);
};

