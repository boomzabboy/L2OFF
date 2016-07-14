
#include <windows.h>
#include <fstream>
#include <sstream>
#include <Cached/Cached.h>
#include <NPCd/NPCd.h>
#include <Server/Server.h>
#include <Common/Config.h>
#include <Common/Utils.h>

static unsigned char WriteProcessMemoryCopyBuffer[0x38+5];
BOOL(*WriteProcessMemoryCopy)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*) = 0;

BOOL WriteProcessMemoryFake(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *pNumberOfBytesWritten)
{
	std::ofstream ofs("writeprocessmemory.txt", std::ios::app);
	ofs << lpBaseAddress;
	for (size_t i(0) ; i < nSize ; ++i) {
		char buffer[3];
		sprintf_s(buffer, "%02X", static_cast<const unsigned char*>(lpBaseAddress)[i]);
		ofs << " " << buffer;
	}
	ofs << " =>";
	for (size_t i(0) ; i < nSize ; ++i) {
		char buffer[3];
		sprintf_s(buffer, "%02X", static_cast<const unsigned char*>(lpBuffer)[i]);
		ofs << " " << buffer;
	}
	if (nSize == 4) {
		UINT32 a1 = *static_cast<const UINT32*>(lpBaseAddress);
		UINT32 a2 = *static_cast<const UINT32*>(lpBuffer);
		ofs << " - maybe address? "
			<< reinterpret_cast<void*>(
				reinterpret_cast<UINT32>(lpBaseAddress) + 4 + a1)
			<< " => "
			<< reinterpret_cast<void*>(
				reinterpret_cast<UINT32>(lpBaseAddress) + 4 + a2);
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

	unsigned char id[16];
	ReadMemoryBYTES(0x401000, id, 16);

	if (!memcmp(id, "\x48\x8D\x05\xC1\x06\x64\x00\xC6\x41\x08\x00\x48\x89\x01\x48\x8B", 16)) {
	    Server::Init();
	} else if (!memcmp(id, "\x48\x8D\x05\x09\x9D\x1E\x00\x48\x89\x01\xE9\x11\x63\x1A\x00\xCC", 16)) {
		Cached::Init();
	} else if (!memcmp(id, "\x4D\x85\xC0\x74\x16\x0F\xB7\x02\x66\x39\x01\x75\x11\x48\x83\xC1", 16)) {
		NPCd::Init();
	} else {
		wchar_t buffer[1024];
		wsprintf(buffer, L"Unknown ID %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
			id[0], id[1], id[2], id[3], id[4], id[5], id[6], id[7], id[8], id[9], id[10], id[11], id[12], id[13], id[14], id[15]);
		MessageBox(0, buffer, L"Error", 0);
		return FALSE;
	}

	return TRUE;
}
