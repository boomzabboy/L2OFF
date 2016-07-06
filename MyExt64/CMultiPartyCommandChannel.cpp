
#include "CMultiPartyCommandChannel.h"
#include "CParty.h"
#include "CUser.h"
#include "Utils.h"
#include "CLog.h"
#include "xvector.h"

void CMultiPartyCommandChannel::Init()
{
}

void CMultiPartyCommandChannel::SendRelationUpdates()
{
	std::vector<CParty*> parties = GetAllParty();
	for (std::vector<CParty*>::iterator i(parties.begin()) ; i != parties.end() ; ++i) {
		std::vector<CUser*> members = (*i)->GetAllMember();
		for (std::vector<CUser*>::iterator j(members.begin()) ; j != members.end() ; ++j) {
			(*j)->SendRelationChanged(0);
		}
	}
}

std::vector<CParty*> CMultiPartyCommandChannel::GetAllParty()
{
	xvector<CParty*> parties;
	GetAllParty(&parties);
	return parties;
}

void CMultiPartyCommandChannel::GetAllParty(xvector<CParty*> *parties)
{
	reinterpret_cast<void(*)(CMultiPartyCommandChannel*, xvector<CParty*>*)>(0x6EF204)(this, parties);
}
