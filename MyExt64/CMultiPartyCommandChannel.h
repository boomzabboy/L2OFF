
#pragma once

#include <vector>
#include "xvector.h"

class CMultiPartyCommandChannel {
public:
	static void Init();
	void SendRelationUpdates();
	std::vector<class CParty*> GetAllParty();
	void GetAllParty(xvector<class CParty*> *parties);
};

