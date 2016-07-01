
#include <windows.h>
#include <fstream>
#include <sstream>
#include "MyExt64.h"
#include "Config.h"
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

	Config::Init();

	{
		std::wstringstream ss;
		ss << config->server.loadDlls;
		while (ss) {
			std::wstring line;
			std::wstring filename;
			ss >> filename;
			if (ss) {
				if (!LoadLibrary(filename.c_str())) {
					std::wstringstream s;
					s << "Can't load " << filename;
					MessageBox(0, s.str().c_str(), L"Error", 16);
					return FALSE;
				}
			}
		}
	}

	MyExt64::SetProtocolVersion(config->server.protocolVersion);
	MyExt64::SetDebug(config->server.debug);
	MyExt64::Init();

	return TRUE;
}
