
#pragma once

#include <windows.h>

class CYieldLock {
public:
	CYieldLock();
	~CYieldLock();
	void Enter(const wchar_t *filename, const unsigned int line);
	void Leave(const wchar_t *filename, const unsigned int line);

protected:
	unsigned char unknown[0xC];
};

