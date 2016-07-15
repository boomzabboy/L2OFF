
#include <Cached/Cached.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void Cached::Init()
{
	DisableSendMail();
	HookStart();
	ChangePaths();
}

void Cached::DisableSendMail()
{
	NOPMemory(0x4623C9, 5);
	NOPMemory(0x463066, 5);
}

void Cached::HookStart()
{
	WriteInstructionCall(0x44C28D, reinterpret_cast<UINT32>(StartHook));
	WriteInstructionCall(0x44C258, reinterpret_cast<UINT32>(CreateWindowEx), 0x44C258 + 6);
}

void Cached::ChangePaths()
{
	ReplaceString(0x5ECCE8, L"IMPORT_FILES", L"script");
	ReplaceString(0x5ECE50, L"IMPORT_FILES", L"script");
	ReplaceString(0x5ECF98, L"IMPORT_FILES", L"script");
	ReplaceString(0x62DC28, L"IMPORT_FILES", L"script");
	ReplaceString(0x663B20, L"IMPORT_FILES", L"script");
}

HWND Cached::CreateWindowEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	std::wstring name(lpWindowName);
	name += L" - patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)";
	return ::CreateWindowEx(dwExStyle, lpClassName, name.c_str(), dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void Cached::StartHook(void *logger, int level, const char *fmt)
{ GUARDED

	reinterpret_cast<void(*)(void*, int, const char*)>(0x47E8AC)(logger, level, fmt);
	CLog::Add(CLog::Blue, L"Patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)");
	ShellExecute(0, L"open", L"cmd.exe", L"/C mkdir bak", 0, SW_HIDE);
	ShellExecute(0, L"open", L"cmd.exe", L"/C move LinError.txt.*.bak bak\\", 0, SW_HIDE);
}

