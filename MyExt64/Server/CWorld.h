
#pragma once

class CWorld {
private:
	CWorld();
	CWorld(const CWorld &other);
	~CWorld();

public:
	static void Init();

	static CWorld* Instance();

	static bool __cdecl PutItemNPCDropWrapper(CWorld *self, class CItem *item, class FVector &pos, class CNPC *npc);

	bool PutItemNPCDrop(class CItem *item, class FVector &pos, class CNPC *npc);
	bool PutItem(class CItem *item, class FVector &pos, class CNPC *npc);
	bool PickItem(class CItem *item, class CUser *user);
};

