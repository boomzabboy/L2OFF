
#pragma once

#include <windows.h>

class CDB {
private:
	CDB();
	CDB(const CDB &other);
	~CDB();

public:
	static CDB* Instance();

	void RequestMarkInZoneRestriction(UINT32 userDbId, UINT32 zoneId, UINT32 time, UINT32 count, bool b, UINT32 i);
};

