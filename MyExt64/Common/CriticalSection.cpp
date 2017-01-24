
#include <Common/CriticalSection.h>

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

ScopedLock::ScopedLock(const ScopedLock &other) :
	cs(other.cs),
	released(other.released)
{
}

ScopedLock& ScopedLock::operator=(const ScopedLock &other)
{
	return *this;
}

ScopedLock::ScopedLock(CriticalSection &cs) :
	cs(cs),
	released(false)
{
	cs.Lock();
}

ScopedLock::~ScopedLock()
{
	Release();
}

void ScopedLock::Release()
{
	if (!released) {
		cs.UnLock();
		released = true;
	}
}