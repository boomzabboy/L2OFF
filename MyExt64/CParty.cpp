
#include "CParty.h"
#include "CUser.h"

void CParty::Init()
{
}

void CParty::Withdraw(CUser *user, const bool b)
{
	reinterpret_cast<void(*)(CParty*, CUser*, const bool)>(0x7844B8)(this, user, b);
}

