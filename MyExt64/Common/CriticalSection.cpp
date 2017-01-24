
#include <Common/CriticalSection.h>
#include <Common/CLog.h>

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

Sync::Sync(const Sync &other)
{
}

Sync& Sync::operator=(const Sync &other)
{
	return *this;
}

Sync::Sync()
{
    sem = CreateSemaphore(0, 0, 1, 0);
	if (!sem) {
		CLog::Add(CLog::Red, L"Can't create semaphore: error %d", GetLastError());
	}
}

Sync::~Sync()
{
	if (sem) {
		ReleaseSemaphore(sem, 1, 0);
		CloseHandle(sem);
	}
}

bool Sync::Wait(int timeout)
{
	if (!sem) {
		return false;
	}
	CLog::Add(CLog::Blue, L"WaitForSingleObject");
	if (WaitForSingleObject(sem, timeout)) {
		return false;
	} else {
		return true;
	}
}

void Sync::Signal()
{
	if (sem) {
		CLog::Add(CLog::Blue, L"ReleaseSemaphore");
		ReleaseSemaphore(sem, 1, 0);
	}
}

