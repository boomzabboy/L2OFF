
#include "CriticalSection.h"

CriticalSection::CriticalSection(const CriticalSection &other)
{
}

CriticalSection& CriticalSection::operator=(const CriticalSection &other)
{
	return *this;
}

CriticalSection::CriticalSection()
{
	InitializeCriticalSection(&cs);
}

void CriticalSection::Lock()
{
	EnterCriticalSection(&cs);
}

void CriticalSection::UnLock()
{
	LeaveCriticalSection(&cs);
}

ScopedLock::ScopedLock(const ScopedLock &other)
  : cs(other.cs)
{
}

ScopedLock& ScopedLock::operator=(const ScopedLock &other)
{
	return *this;
}

ScopedLock::ScopedLock(CriticalSection &cs)
 : cs(cs)
{
	cs.Lock();
}

ScopedLock::~ScopedLock()
{
	cs.UnLock();
}

