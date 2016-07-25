
#include <Server/CWorld.h>
#include <Server/CItem.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/CSummon.h>
#include <Server/CParty.h>
#include <Server/CNPC.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/CSharedCreatureData.h>

void CWorld::Init()
{
	WriteInstructionCall(0x71CA14, reinterpret_cast<UINT32>(PutItemNPCDropWrapper));
}

CWorld* CWorld::Instance()
{
	return reinterpret_cast<CWorld*>(0x124239A0);
}

bool __cdecl CWorld::PutItemNPCDropWrapper(CWorld *self, CItem *item, FVector &pos, CNPC *npc)
{
	return self->PutItemNPCDrop(item, pos, npc);
}

bool CWorld::PutItemNPCDrop(CItem *item, FVector &pos, CNPC *npc)
{
	if (!item) {
		return false;
	}

	if (npc->IsBoss() && !Config::Instance()->autoLoot->autoLootBossDrop) {
		return PutItem(item, pos, npc);
	}

	if (!npc->IsBoss() && !Config::Instance()->autoLoot->autoLootMobDrop) {
		return PutItem(item, pos, npc);
	}

	if (Config::Instance()->autoLoot->excludedItems.count(item->itemId)) {
		return PutItem(item, pos, npc);
	}

	CContributeData *contributeData = item->GetContributeData();
	if (!contributeData) {
		return PutItem(item, pos, npc);
	}

	CObject *looterObject = contributeData->GetLooter();
	if (!looterObject) {
		return PutItem(item, pos, npc);
	}

	CUser *looter = 0;

	CCreature *creature = reinterpret_cast<CCreature*>(looterObject);
	if (creature) {
		if (creature->IsUser()) {
			looter = reinterpret_cast<CUser*>(creature);
		} else if (creature->IsSummon()) {
			looter = reinterpret_cast<CSummon*>(creature)->GetUserOrMaster();
		}
	} else {
		CParty *party = reinterpret_cast<CParty*>(looterObject);
		if (party->IsParty()) {
			looter = party->GetMaster();
		}
	}

	if (!looter || !looter->ext.autoloot || !contributeData->PickableIn5Sec(looter)) {
		return PutItem(item, pos, npc);
	}

	CUserSocket *socket = looter->socket;
	if (!socket) {
		return PutItem(item, pos, npc);
	}

	double maxd = Config::Instance()->autoLoot->maximumAutoLootDistance;
	if (maxd >= 0) {
		double dx = looter->sd->x - pos.x;
		double dy = looter->sd->y - pos.y;
		double dz = looter->sd->z - pos.z;
		if (dx * dx + dy * dy + dz * dz > maxd * maxd) {
			return PutItem(item, pos, npc);
		}
	}

	if (!looter->AddItemToInventory2(item)) {
		return PutItem(item, pos, npc);
	}

	return true;

}

bool CWorld::PutItem(CItem *item, FVector &pos, CNPC *npc)
{
	return reinterpret_cast<bool(*)(CWorld*, CItem*, FVector&, CNPC*)>(0x979464)(
		this, item, pos, npc);
}

