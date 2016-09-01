
#include <Server/CObjectDB.h>

CObjectDB* CObjectDB::Instance()
{
	return reinterpret_cast<CObjectDB*>(0xE3DB6D0);
}

int CObjectDB::GetClassIdFromName(const wchar_t *name) const
{
	return reinterpret_cast<int(*)(const CObjectDB*, const wchar_t*)>(0x76199C)(this, name);
}

