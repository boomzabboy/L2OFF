
#include <NPCd/NPCd.h>
#include <NPCd/SplitAI.h>
#include <NPCd/Compiler.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/Config.h>

void NPCd::Init()
{
	DisableSendMail();
	HookStart();
	ChangePaths();
	if (Config::Instance()->npcd->useSplitAI) {
		SplitAI::Init();
	}
	Compiler::Init();
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
	if (!Compiler::filename.empty()) {
		name += L" - NASC COMPILE MODE";
	}
	name += L" - patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)";
	return ::CreateWindowEx(dwExStyle, lpClassName, name.c_str(), dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void NPCd::StartHook(void *logger, int level, const char *fmt)
{ GUARDED

	reinterpret_cast<void(*)(void*, int, const char*)>(0x478038)(logger, level, fmt);
	CLog::Add(CLog::Blue, L"Patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)");
	CLog::Add(CLog::Blue, L" ");
	CLog::Add(CLog::Blue, L"To use l2npc.exe as a NASC compiler, run it with parameters:");
	CLog::Add(CLog::Blue, L" ");
	if (Compiler::exeFilename.size() < 2048) {
		CLog::Add(CLog::Blue, L"    %s [-c|--close] FILENAME", Compiler::exeFilename.c_str());
	} else {
		CLog::Add(CLog::Blue, L"    %s [-c|--close] FILENAME", Compiler::exeFilename.substr(0, 2048).c_str());
	}
	CLog::Add(CLog::Blue, L" ");
	CLog::Add(CLog::Blue, L"    -c, --close         Close after successful compilation");
	CLog::Add(CLog::Blue, L"    FILENAME            NASC file to compile");
	CLog::Add(CLog::Blue, L" ");

	ShellExecute(0, L"open", L"cmd.exe", L"/C mkdir bak", 0, SW_HIDE);
	ShellExecute(0, L"open", L"cmd.exe", L"/C move LinError.txt.*.bak bak\\", 0, SW_HIDE);
}

