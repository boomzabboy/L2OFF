
#include <Server/CWorld.h>
#include <Server/CItem.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/CSummon.h>
#include <Server/CNPC.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CLog.h>
#include <algorithm>
#include <map>
#include <vector>

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

template<class T>
class second_less {
public:
	bool operator()(const T &v1, const T &v2)
	{
		return v1.second < v2.second;
	}
};

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

	std::vector<std::pair<CUser*, double> > contributors;
	double maxd = Config::Instance()->autoLoot->maximumAutoLootDistance;

	for (std::map<UINT32, double>::const_iterator i = contributeData->data.begin() ; i != contributeData->data.end() ; ++i) {

		CCreature *creature = reinterpret_cast<CCreature*>(CObject::GetObject(i->first));

		if (!creature) {
			continue;
		}

		if (!creature->IsUser()) {
			if (!creature->IsSummon()) {
				continue;
			}

			creature = reinterpret_cast<CSummon*>(creature)->GetUserOrMaster();

			if (!creature || !creature->IsUser()) {
				continue;
			}
		}

		CUser *contributor = reinterpret_cast<CUser*>(creature);

		if (!contributor->ext.autoloot || !contributor->socket || !contributeData->PickableIn5Sec(contributor)) {
			continue;
		}

		if (maxd >= 0) {
			double dx = contributor->sd->x - pos.x;
			double dy = contributor->sd->y - pos.y;
			double dz = contributor->sd->z - pos.z;
			if (dx * dx + dy * dy + dz * dz > maxd * maxd) {
				continue;
			}
		}

		contributors.push_back(std::make_pair(contributor, i->second));
	}

	if (contributors.empty()) {
		return PutItem(item, pos, npc);
	}

	std::sort(contributors.begin(), contributors.end(), second_less<std::pair<CUser*, double> >());

	CUser *looter = contributors.back().first;

	CUserSocket *socket = looter->socket;
	if (!socket) {
		return PutItem(item, pos, npc);
	}

	item->worldInfo->x = looter->sd->x;
	item->worldInfo->y = looter->sd->y;
	item->worldInfo->z = looter->sd->z;
	bool oldPickable = item->worldInfo->pickable;
	item->worldInfo->pickable = true;
	if (!PickItem(item, looter)) {
		item->worldInfo->pickable = oldPickable;
		return PutItem(item, pos, npc);
	}

	return true;
}

bool CWorld::PutItem(CItem *item, FVector &pos, CNPC *npc)
{
	return reinterpret_cast<bool(*)(CWorld*, CItem*, FVector&, CNPC*)>(0x979464)(
		this, item, pos, npc);
}

bool CWorld::PickItem(CItem *item, CUser *user)
{
	return reinterpret_cast<bool(*)(CWorld*, CItem*, CUser*)>(0x974400)(
		this, item, user);
}