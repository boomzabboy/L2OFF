
#include "CYieldLock.h"

CYieldLock::CYieldLock()
{
}

CYieldLock::~CYieldLock()
{
}

void CYieldLock::Enter(const wchar_t *filename, const unsigned int line)
{
	reinterpret_cast<void(__thiscall*)(CYieldLock*, const wchar_t*, const unsigned int)>(0x97E9D4)(this, filename, line);
}

void CYieldLock::Leave(const wchar_t *filename, const unsigned int line)
{
	reinterpret_cast<void(__thiscall*)(CYieldLock*, const wchar_t*, const unsigned int)>(0x97EA74)(this, filename, line);
}

