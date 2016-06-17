
#include <windows.h>
#include <fstream>
#include <sstream>
#include "MyExt64.h"
#include "Utils.h"

__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hDllModule, DWORD reason, LPVOID pReserved)
{
	(void) hDllModule;
	(void) pReserved;

	if (reason != DLL_PROCESS_ATTACH) {
		return TRUE;
	}

    server = OpenProcess(
        PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE,
        FALSE, GetCurrentProcessId());

	// load all dlls mentioned in file MyExt64.load
	std::wifstream ifs(L"MyExt64.load");
	while (ifs) {
		std::wstring line;
		std::wstring filename;
		ifs >> filename;
		if (ifs) {
			if (!LoadLibrary(filename.c_str())) {
				std::wstringstream s;
				s << "Can't load " << filename;
				MessageBox(0, s.str().c_str(), L"Error", 16);
				return FALSE;
			}
		}
	}

	MyExt64::Init();

	return TRUE;
}
