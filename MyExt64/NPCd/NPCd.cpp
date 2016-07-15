
#include <NPCd/NPCd.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void NPCd::Init()
{
	DisableSendMail();
	HookStart();
	ChangePaths();
}

void NPCd::DisableSendMail()
{
	NOPMemory(0x42CD41, 5);
	NOPMemory(0x42CDBE, 5);
}

void NPCd::HookStart()
{
	WriteInstructionCall(0x4759C7, reinterpret_cast<UINT32>(StartHook));
	WriteInstructionCall(0x474D11, reinterpret_cast<UINT32>(CreateWindowEx), 0x474D11 + 6);
}

void NPCd::ChangePaths()
{
	ReplaceString(0x649CA8, L"IMPORT", L"script");
	ReplaceString(0x649C70, L"IMPORT", L"script");
	ReplaceString(0x649E50, L"IMPORT", L"script");
}

HWND NPCd::CreateWindowEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	std::wstring name(lpWindowName);
	name += L" - patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)";
	return ::CreateWindowEx(dwExStyle, lpClassName, name.c_str(), dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void NPCd::StartHook(void *logger, int level, const char *fmt)
{ GUARDED

	reinterpret_cast<void(*)(void*, int, const char*)>(0x478038)(logger, level, fmt);
	CLog::Add(CLog::Blue, L"Patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)");
}

