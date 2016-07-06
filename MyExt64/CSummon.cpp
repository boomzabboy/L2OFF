
#include "CSummon.h"
#include "Utils.h"
#include "Config.h"
#include "CUser.h"
#include "CParty.h"

void CSummon::Init()
{
    WriteMemoryQWORD(0xBCB498, reinterpret_cast<UINT64>(IsEnemyToWrapper));
}

bool CSummon::IsEnemyTo(CCreature *creature)
{
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

