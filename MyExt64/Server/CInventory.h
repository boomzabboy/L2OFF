
#pragma once

class CInventory {
public:
	static void Init();

	static class CItem* GetByServerIDIgnoreMoreStacks(CInventory *self, int id);

	class CCreature* GetOwner();

	/* 0x0000 */ unsigned char padding0x0000[0x00C8 - 0x0000];
	/* 0x00C8 */ unsigned char noDropItems;
	/* 0x00C9 */ unsigned char padding0x00C9[0x00D0 - 0x00C9];
	/* 0x00D0 */
};

