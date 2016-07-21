
#include <Server/CDB.h>

CDB::CDB()
{
}

CDB::CDB(const CDB &other)
{
}

CDB::~CDB()
{
}

CDB* CDB::Instance()
{
	return reinterpret_cast<CDB*>(0x149AE80);
}

void CDB::RequestMarkInZoneRestriction(UINT32 userDbId, UINT32 zoneId, UINT32 time, UINT32 count, bool b, UINT32 i)
{
	reinterpret_cast<void(*)(CDB*, UINT32, UINT32, UINT32, UINT32, bool, UINT32)>(0x594D3C)(
		this, userDbId, zoneId, time, count, b, i);
}

