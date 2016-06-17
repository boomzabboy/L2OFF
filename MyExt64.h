
#pragma once

#include <windows.h>

class MyExt64 {
public:
	static const int ProtocolVersionGraciaFinal;
	static const int ProtocolVersionGraciaFinalUpdate1;
	static const int ProtocolVersionGraciaEpilogue;
	static const int ProtocolVersionGraciaEpilogueUpdate1;

	static void Init();
	static int GetProtocolVersion();

protected:
	static void SetProtocolVersion(int version);
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
	static void HookOnLoadEnd();

	static void __cdecl OnLoadEnd(UINT64 classBase);

	static int protocolVersion;
};

