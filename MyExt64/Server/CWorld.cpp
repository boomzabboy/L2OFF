
#include <Server/CWorld.h>
#include <Server/CItem.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/CSummon.h>
#include <Server/CNPC.h>
#include <Server/Server.h>
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
	NOPMemory(0x968739, 5);
	NOPMemory(0x96903C, 5);
	NOPMemory(0x9695FF, 5);
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
		if (npc) {
			CLog::Debug(CLog::Blue,
				L"CWorld::PutItemNPCDrop(item = null, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): ignore",
				pos.x, pos.y, pos.z, npc->GetName());
		} else {
			CLog::Debug(CLog::Blue,
				L"CWorld::PutItemNPCDrop(item = null, pos = {x = %f, y = %f, z = %f}, npc = null): ignore",
				pos.x, pos.y, pos.z);
		}
		return false;
	}

	if (!npc) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = null): "
			L"no npc, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z);
		return PutItem(item, pos, npc);
	}

	CLog::Debug(CLog::Blue,
		L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s})",
		item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());

	if (npc->IsBoss() && !Config::Instance()->autoLoot->autoLootBossDrop) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"boss but boss autoloot disabled, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		return PutItem(item, pos, npc);
	}

	if (!npc->IsBoss() && !Config::Instance()->autoLoot->autoLootMobDrop) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"mob but mob autoloot disabled, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		return PutItem(item, pos, npc);
	}

	if (Config::Instance()->autoLoot->excludedItems.count(item->itemId)) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"excluded item, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		return PutItem(item, pos, npc);
	}

	CContributeData *contributeData = item->GetContributeData();
	if (!contributeData) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"no contribution data, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
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

		if (!contributor->sd->isAlive
			|| !contributor->ext.autoloot
			|| !contributor->socket
			|| !contributeData->PickableIn5Sec(contributor)) {

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
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"no suitable contributors, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		return PutItem(item, pos, npc);
	}

	std::sort(contributors.begin(), contributors.end(), second_less<std::pair<CUser*, double> >());

	CUser *looter = contributors.back().first;

	CUserSocket *socket = looter->socket;
	if (!socket) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"looter has no socket, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		return PutItem(item, pos, npc);
	}

	item->worldInfo->x = looter->sd->x;
	item->worldInfo->y = looter->sd->y;
	item->worldInfo->z = looter->sd->z;
	bool oldPickable = item->worldInfo->pickable;
	item->worldInfo->pickable = true;
	if (!PickItem(item, looter)) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
			L"couldn't pick item, drop it to the ground",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
		item->worldInfo->pickable = oldPickable;
		return PutItem(item, pos, npc);
	}

	CLog::Debug(CLog::Blue,
		L"CWorld::PutItemNPCDrop(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s}): "
		L"picked item",
		item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
	return true;
}

bool CWorld::PutItem(CItem *item, FVector &pos, CNPC *npc)
{
	if (item && npc) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItem(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = {name = %s})",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z, npc->GetName());
	} else if (item) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItem(item = {type = %lu, count = %llu}, pos = {x = %f, y = %f, z = %f}, npc = null)",
			item->itemId, item->worldInfo->count, pos.x, pos.y, pos.z);
		return false;
	} else if (npc) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItem(item = null, pos = {x = %f, y = %f, z = %f}, npc = {name = %s})",
			pos.x, pos.y, pos.z, npc->GetName());
		return false;
	} else {
		CLog::Debug(CLog::Blue,
			L"CWorld::PutItem(item = null, pos = {x = %f, y = %f, z = %f}, npc = null)",
			pos.x, pos.y, pos.z);
		return false;
	}

	return reinterpret_cast<bool(*)(CWorld*, CItem*, FVector&, CNPC*)>(0x979464)(
		this, item, pos, npc);
}

bool CWorld::PickItem(CItem *item, CUser *user)
{
	if (item && user) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PickItem(item = {type = %lu, count = %llu}, user = {name = %s})",
			item->itemId, item->worldInfo->count, user->GetName());
	} else if (item) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PickItem(item = {type = %lu, count = %llu}, user = null",
			item->itemId, item->worldInfo->count);
	} else if (user) {
		CLog::Debug(CLog::Blue,
			L"CWorld::PickItem(item = null, user = {name = %s})",
			user->GetName());
	} else {
		CLog::Debug(CLog::Blue,
			L"CWorld::PickItem(item = null, user = null");
	}
	return reinterpret_cast<bool(*)(CWorld*, CItem*, CUser*)>(0x974400)(
		this, item, user);
}