
#pragma once

#include <windows.h>

class CDB {
private:
	CDB();
	CDB(const CDB &other);
	~CDB();

public:
	static void Init();
	static CDB* Instance();

	static void __cdecl SendSaveCharacterInfoWrapper(CDB *self, class CUser *user, bool a, bool b);

	void RequestMarkInZoneRestriction(UINT32 userDbId, UINT32 zoneId, UINT32 time, UINT32 count, bool b, UINT32 i);
	void RequestLoadUserPoint(class CUser *user, int type);
	void SendSaveCharacterInfo(class CUser *user, bool a, bool b);
	void SetDailyQuest(UINT32 charId, UINT32 questId, UINT32 completeTime);
};

