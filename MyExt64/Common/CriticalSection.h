
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

