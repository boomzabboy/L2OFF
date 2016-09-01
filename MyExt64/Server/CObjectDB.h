
#pragma once

class CObjectDB {
private:
	CObjectDB();
	CObjectDB(const CObjectDB &other);
	~CObjectDB();

public:
	static CObjectDB* Instance();

	int GetClassIdFromName(const wchar_t *name) const;
};

