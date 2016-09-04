
#pragma once

#include <Common/CriticalSection.h>

class Server {
public:
	enum ProtocolVersion {
		ProtocolVersionGraciaFinal = 83,
		ProtocolVersionGraciaFinalUpdate1 = 87,
		ProtocolVersionGraciaEpilogue = 148,
		ProtocolVersionGraciaEpilogueUpdate1 = 152
	};

	class Plugin {
	public:
		virtual void init(unsigned char *data, CriticalSection &cs) = 0;
		virtual void decrypt(unsigned char *data, CriticalSection &cs, BYTE *packet, int packetLen, BYTE opcode) = 0;
	};

	static void Init();
	static void SetDebug(bool debug);
	static bool IsDebug();
	static void SetProtocolVersion(int version);
	static int GetProtocolVersion();
	static Plugin* GetPlugin();

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
	static void InitClanRestrictions();
	static void ApplyMiscMXCFixes();
	static void SetBuffSlots();
	static void SetFixedPCCafePoints(const INT32 points);
	static void SetVitalityLevels();
	static void RemoveKamaelRace();
	static void RelogKeepSongsDances();

	static void __cdecl OnLoadEnd(UINT64 classBase);

	static void __cdecl CPledgeInitPledge();
	static void __cdecl CDominionInitDominion();

	static int protocolVersion;
	static bool debug;
	static CriticalSection pledgeInitCS;
	static bool pledgeInitialized;
	static Plugin *plugin;
};

