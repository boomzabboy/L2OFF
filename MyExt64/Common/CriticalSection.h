
#pragma once

#include <windows.h>

class CriticalSection {
private:
	CriticalSection(const CriticalSection &other);
	CriticalSection& operator=(const CriticalSection &other);

public:
	CriticalSection();
	void Lock();
	void UnLock();

protected:
	CRITICAL_SECTION cs;
};

class ScopedLock {
protected:
	ScopedLock(const ScopedLock &other);
	ScopedLock& operator=(const ScopedLock &other);

public:
	ScopedLock(CriticalSection &cs);
	~ScopedLock();
	void Release();

protected:
	CriticalSection &cs;
	bool released;
};

class Sync {
private:
	Sync(const Sync &other);
	Sync& operator=(const Sync &other);

public:
	Sync();
	~Sync();
	bool Wait(int timeout);
	void Signal();

protected:
	HANDLE sem;
};

