
#include <windows.h>
#include <winnt.h>

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	if (!CreateProcess(L"L2Server.exe", 0, 0, 0, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
		MessageBox(0, L"Can't start L2Server.exe", L"Error", 0);
		return 1;
	}
	SIZE_T bytes;
	void *buffer = VirtualAllocEx(pi.hProcess, 0, 0x100, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	const wchar_t *name = L"MyExt64.dll";
	WriteProcessMemory(pi.hProcess, buffer, name, wcslen(name) * 2 + 2, &bytes);
	HANDLE hThread = CreateRemoteThread(pi.hProcess, 0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibrary), buffer, 0, 0);
	if (!hThread) {
		TerminateProcess(pi.hProcess, 0);
		MessageBox(0, L"Can't inject MyExt64.dll into L2Server.exe", L"Error", 0);
		return 1;
	}
	DWORD status = 0;
	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &status);
	ReadProcessMemory(pi.hProcess, reinterpret_cast<void*>(0x5EA1E2), buffer, 5, &bytes);
	if (memcmp(buffer, "\x66\x31\xF6\x90\x90", 5)) {
		TerminateProcess(pi.hProcess, 0);
		MessageBox(0, L"Failed to load MyExt64.dll into L2Server.exe", L"Error", 0);
		return 1;
	}
	ResumeThread(pi.hThread);
	return 0;
}

