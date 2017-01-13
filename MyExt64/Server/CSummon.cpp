
#include <Server/CSummon.h>
#include <Server/CUser.h>
#include <Server/CParty.h>
#include <Server/NpcServer.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/CLog.h>

void CSummon::Init()
{
	WriteMemoryQWORD(0xBCB498, reinterpret_cast<UINT64>(IsEnemyToWrapper));
	WriteMemoryQWORD(0xBCB508, reinterpret_cast<UINT64>(OutOfSightWrapper));
}

bool CSummon::IsEnemyTo(CCreature *creature)
{
	GUARDED;

	bool ret = reinterpret_cast<bool(*)(CSummon*, CCreature*)>(0x7ABBD8)(this, creature);
	if (!Config::Instance()->fixes->commandChannelFriendly) {
		return ret;
	}

	CUser *owner = GetUserOrMaster();
	if (!owner) {
		return ret;
	}

	CParty *party = owner->GetParty();
	CMultiPartyCommandChannel *channel = owner->GetMPCC();

	if (creature->IsUser()) {
		CUser *user = reinterpret_cast<CUser*>(creature);
		if (user == owner) {
			ret = false;
		} else if (party && user->GetParty() == party) {
			ret = false;
		} else if (channel && user->GetMPCC() == channel) {
			ret = false;
		}
		return ret;
	}

	if (creature->IsSummon()) {
		CSummon *summon2 = reinterpret_cast<CSummon*>(creature);
		CUser *owner2 = summon2->GetUserOrMaster();
		if (owner2) {
			if (owner2 == owner) {
				ret = false;
			} else if (party && owner2->GetParty() == party) {
				ret = false;
			} else if (channel && owner2->GetMPCC() == channel) {
				ret = false;
			}
		}
		return ret;
	}

	return ret;
}

CUser* CSummon::GetUserOrMaster()
{
	return reinterpret_cast<CUser*(*)(CSummon*)>(0x7AB6E8)(this);
}

bool CSummon::IsEnemyToWrapper(CSummon *self, CCreature *creature)
{
	return self->IsEnemyTo(creature);
}

void __cdecl CSummon::OutOfSightWrapper(CSummon *self, CObject *object, bool b)
{
	self->OutOfSight(object, b);
}

void CSummon::OutOfSight(CObject *object, bool b)
{
	GUARDED;

	CCreature *creature = reinterpret_cast<CCreature*>(object);
	if (creature->IsValidCreature()) {
		if (targetId == creature->objectId) {
			DoNothing();
			ChangeTarget(0, 2);
			NpcServer::Instance()->Send("cdddddd", 0x37, objectId, 2, 0, 0, 0, 0x11);
		}
	}
}

