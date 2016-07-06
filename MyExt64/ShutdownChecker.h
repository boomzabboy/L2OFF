
#pragma once

#include <windows.h>

class ShutdownChecker {
public:
	static void Init();
	static void StartChecking();
	static DWORD CheckForShutdown(void *v);
};

