
#pragma once

#include <vector>
#include <Common/xvector.h>

class CMultiPartyCommandChannel {
public:
	static void Init();
	void SendRelationUpdates();
	std::vector<class CParty*> GetAllParty();
	std::vector<class CUser*> GetAllMember();
	void GetAllParty(xvector<class CParty*> *parties);
	void GetAllMember(xvector<class CUser*> *users);
};

