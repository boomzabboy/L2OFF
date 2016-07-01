
#include "GraciaEpilogue.h"

void GraciaEpilogue::Init()
{
	InitPackets();
	InitBuySell();
	InitSkillEnchant();
}

void GraciaEpilogue::Load()
{
	LoadSkillEnchant();
}

