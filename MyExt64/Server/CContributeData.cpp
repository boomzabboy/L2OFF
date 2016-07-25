
#include <Server/CContributeData.h>
#include <Server/CUser.h>
#include <Server/CSummon.h>

CObject* CContributeData::GetLooter()
{
	return reinterpret_cast<CObject*(*)(UINT32*)>(0x86E3D0)(&looterObjectId);
}

bool CContributeData::PickableIn5Sec(CCreature *creature)
{
	return reinterpret_cast<bool(*)(CContributeData*, CCreature*)>(0x758504)(this, creature);
}

