
#include <windows.h>
#include <winnt.h>
#include <sstream>

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	if (!CreateProcess(L"L2Server.exe", 0, 0, 0, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		MessageBox(0, L"Can't start L2Server.exe", L"Error", 0);
		return 1;
	}
	
    HANDLE hProcess = OpenProcess(
        PROCESS_ALL_ACCESS | PROCESS_VM_READ | PROCESS_VM_WRITE,
		FALSE, pi.dwProcessId);

	SIZE_T bytes;
	void *buffer = VirtualAllocEx(hProcess, 0, 0x100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	const wchar_t *name = L"MyExt64.dll";
	WriteProcessMemory(hProcess, buffer, name, wcslen(name) * 2 + 2, &bytes);
	HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibrary), buffer, 0, 0);
	if (!hThread) {
		TerminateProcess(hProcess, 0);
		MessageBox(0, L"Can't inject MyExt64.dll into L2Server.exe", L"Error", 0);
		return 1;
	}
	DWORD status = 0;
	for (;;) {
		WaitForSingleObject(hThread, INFINITE);
		if (!GetExitCodeThread(hThread, &status)) {
			std::wstringstream ss;
			ss << "Failed to get thread exit code: " << GetLastError();
			TerminateProcess(hProcess, 0);
			MessageBox(0, ss.str().c_str(), L"Error", 0);
			return 1;
		}
		if (status != STILL_ACTIVE) {
			break;
		}
	}
	ResumeThread(pi.hThread);
	DWORD oldProtect;
	if (!VirtualProtectEx(hProcess, reinterpret_cast<void*>(0x5EA1E2), 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		TerminateProcess(hProcess, 0);
		wchar_t b[1024];
		unsigned char *x = reinterpret_cast<unsigned char*>(buffer);
		wsprintf(b, L"VirtualProtectEx failed: %x", GetLastError());
		MessageBox(0, b, L"Error", 0);
		return 1;
	}
	if (!ReadProcessMemory(hProcess, reinterpret_cast<void*>(0x5EA1E2), buffer, 5, &bytes)) {
		TerminateProcess(hProcess, 0);
		wchar_t b[1024];
		unsigned char *x = reinterpret_cast<unsigned char*>(buffer);
		wsprintf(b, L"ReadProcessMemory failed: %x", GetLastError());
		MessageBox(0, b, L"Error", 0);
		return 1;
	}
	if (memcmp(buffer, "\x66\x31\xF6\x90\x90", 5)) {
		TerminateProcess(hProcess, 0);
		MessageBox(0, L"Failed to load MyExt64.dll into L2Server.exe", L"Error", 0);
		return 1;
	}
	for (;;) {
		WaitForSingleObject(hProcess, INFINITE);
		GetExitCodeProcess(hProcess, &status);
		if (status != STILL_ACTIVE) {
			break;
		}
	}
	return status;
}

