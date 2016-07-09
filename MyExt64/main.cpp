
#include <windows.h>
#include <fstream>
#include <sstream>
#include "MyExt64.h"
#include "Config.h"
#include "Utils.h"

static unsigned char WriteProcessMemoryCopyBuffer[0x38+5]; //1A6];
BOOL(*WriteProcessMemoryCopy)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*) = 0;

BOOL WriteProcessMemoryFake(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *pNumberOfBytesWritten)
{
	std::ofstream ofs("writeprocessmemory.txt", std::ios::app);
	ofs << hProcess << " " << lpBaseAddress;
	for (size_t i(0) ; i < nSize ; ++i) {
		char buffer[3];
		sprintf_s(buffer, "%02X", static_cast<const unsigned char*>(lpBuffer)[i]);
		ofs << " " << buffer;
	}
	ofs << std::endl;
	ofs.close();
	return WriteProcessMemoryCopy(hProcess, lpBaseAddress, lpBuffer, nSize, pNumberOfBytesWritten);
}

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

	WriteProcessMemoryCopy = reinterpret_cast<BOOL(*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*)>(reinterpret_cast<void*>(WriteProcessMemory));

	ReadMemoryBYTES(reinterpret_cast<UINT32>(WriteProcessMemory), WriteProcessMemoryCopyBuffer, 0x38+5);
	DWORD oldProtect;
	VirtualProtectEx(server, WriteProcessMemoryCopyBuffer, 0x38+5, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteInstructionJmp(reinterpret_cast<UINT32>(WriteProcessMemoryCopyBuffer) + 0x38,
		reinterpret_cast<UINT32>(WriteProcessMemory) + 0x38);
	WriteProcessMemoryCopy = reinterpret_cast<BOOL(*)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*)>(
		reinterpret_cast<void*>(WriteProcessMemoryCopyBuffer));

	Config::Instance();

	{
		std::wstringstream ss;
		ss << Config::Instance()->server->loadDlls;
		while (ss) {
			std::wstring line;
			std::wstring filename;
			ss >> filename;
			if (ss && !filename.empty()) {
				bool debug = false;
				if (filename[0] == '!') {
					filename = filename.substr(1);
					debug = true;
					std::ofstream ofs("writeprocessmemory.txt");
					ofs.close();
					DWORD oldProtect;
					VirtualProtectEx(server, WriteProcessMemory, 9, PAGE_EXECUTE_READWRITE, &oldProtect);
					unsigned char *p = reinterpret_cast<unsigned char*>(WriteProcessMemory);
					p[0] = 0x48;
					p[1] = 0xC7;
					p[2] = 0xC0;
					*reinterpret_cast<UINT32*>(p + 3) = reinterpret_cast<UINT32>(WriteProcessMemoryFake);
					p[7] = 0xFF;
					p[8] = 0xE0;
				}
				HMODULE module = LoadLibrary(filename.c_str());
				if (!module) {
					std::wstringstream s;
					s << "Can't load " << filename;
					MessageBox(0, s.str().c_str(), L"Error", 16);
					return FALSE;
				} else if (debug) {
					void *ptr = GetProcAddress(module, "DllMain");
					std::ofstream ofs("writeprocessmemory.txt", std::ios::app);
					ofs << "done" << std::endl;
					MessageBox(0, L"DONE", L"DONE", 0);
					return false;
				}
			}
		}
	}

	MyExt64::SetProtocolVersion(Config::Instance()->server->protocolVersion);
	MyExt64::SetDebug(Config::Instance()->server->debug);
	MyExt64::Init();

	return TRUE;
}
