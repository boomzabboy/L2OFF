
#include <Server/CMultiPartyCommandChannel.h>
#include <Server/CParty.h>
#include <Server/CUser.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/xvector.h>

void CMultiPartyCommandChannel::Init()
{
}

void CMultiPartyCommandChannel::SendRelationUpdates()
{ GUARDED

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
	GUARDED;

	xvector<CParty*> parties;
	GetAllParty(&parties);
	return parties;
}

void CMultiPartyCommandChannel::GetAllParty(xvector<CParty*> *parties)
{
	reinterpret_cast<void(*)(CMultiPartyCommandChannel*, xvector<CParty*>*)>(0x6EF204)(this, parties);
}

std::vector<CUser*> CMultiPartyCommandChannel::GetAllMember()
{
	GUARDED;

	xvector<CUser*> users;
	GetAllMember(&users);
	return users;
}

void CMultiPartyCommandChannel::GetAllMember(xvector<CUser*> *users)
{
	reinterpret_cast<void(*)(CMultiPartyCommandChannel*, xvector<CUser*>*)>(0x6F0070)(this, users);
}

