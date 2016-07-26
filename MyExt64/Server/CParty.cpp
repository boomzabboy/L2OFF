
#include <Server/CParty.h>
#include <Server/CUser.h>
#include <Common/CLog.h>
#include <Common/Utils.h>

void CParty::Init()
{
}

void CParty::Withdraw(CUser *user, const bool b)
{ GUARDED

	reinterpret_cast<void(*)(CParty*, CUser*, const bool)>(0x7844B8)(this, user, b);
}

CUser* CParty::GetMaster()
{ GUARDED

	return reinterpret_cast<CUser*(*)(CParty*)>(0x77D5C0)(this);
}

std::vector<CUser*> CParty::GetAllMember()
{ GUARDED

	xvector<CUser*> members;
	GetAllMember(&members);
	return members;
}

void CParty::GetAllMember(xvector<CUser*> *members)
{
	reinterpret_cast<void(*)(CParty*, xvector<CUser*>*)>(0x77E9D8)(this, members);
}

void CParty::SendRelationChanged()
{ GUARDED

	std::vector<CUser*> members = GetAllMember();
	for (std::vector<CUser*>::iterator i(members.begin()) ; i != members.end() ; ++i) {
		(*i)->SendRelationChanged(0);
	}
}

