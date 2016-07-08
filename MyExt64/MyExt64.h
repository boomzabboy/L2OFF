
#pragma once

#include "CriticalSection.h"

class MyExt64 {
public:
	enum ProtocolVersion {
		ProtocolVersionGraciaFinal = 83,
		ProtocolVersionGraciaFinalUpdate1 = 87,
		ProtocolVersionGraciaEpilogue = 148,
		ProtocolVersionGraciaEpilogueUpdate1 = 152
	};

	static void Init();
	static void SetDebug(bool debug);
	static bool IsDebug();
	static void SetProtocolVersion(int version);
	static int GetProtocolVersion();

protected:
	static void Load();
	static void SetMaxIndex(const size_t index);
	static void DeadlockTimeout(UINT32 timeout);
	static void DisableNoAuthExit();
	static void DisableSendMail();
	static void HideWarnings();
	static void SetShutdownSeconds(const int seconds);
	static void EnableLoadNpcSettingsAnytime();
	static void EnableGlobalShout();
	static void AllowAirshipSkills();
	static void MountUnmountKeepBuffs();
	static void SetPledgeLoadTimeout(time_t timeout);
	static void SetPledgeWarLoadTimeout(time_t timeout);
	static void HookStart();
	static void StartHook(void *logger, int level, const wchar_t *fmt, const wchar_t *build);
	static HWND CreateWindowEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	static void HookLoad();
	static void LoadHook(void *x);
	static void HookOnLoadEnd();
	static void FixLoading();
	static void SetMaxLevel(const int main, const int subClass);

	static void __cdecl OnLoadEnd(UINT64 classBase);

	static void __cdecl CPledgeInitPledge();
	static void __cdecl CDominionInitDominion();

	static int protocolVersion;
	static bool debug;
	static CriticalSection pledgeInitCS;
	static bool pledgeInitialized;
};

