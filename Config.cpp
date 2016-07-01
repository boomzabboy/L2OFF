
#include "Config.h"
#include "MyExt64.h"
#include <windows.h>
#include <sstream>

Config *config = 0;

Config::Config(const wchar_t *filename)
  : filename(filename)
{
	server.name = GetString(L"server", L"Name", L"Server");
	server.protocolVersion = GetInt(L"server", L"ProtocolVersion", MyExt64::ProtocolVersionGraciaEpilogueUpdate1);
	server.debug = GetBool(L"server", L"Debug", false);
	server.maxIndex = GetInt(L"server", L"MaxIndex", 10000);
	server.deadlockTimeout = GetInt(L"server", L"DeadlockTimeout", 300);
	server.shutdownDuration = GetInt(L"server", L"ShutdownDuration", 180);
	server.globalShout = GetBool(L"server", L"GlobalShout", false);
	server.allowLoadNpcSettingsAnyTime = GetBool(L"server", L"AllowLoadNpcSettingsAnyTime", true);
	server.mountKeepBuffs = GetBool(L"server", L"MountKeepBuffs", true);
	server.dismountKeepBuffs = GetBool(L"server", L"DismountKeepBuffs", true);
	server.allowAirshipSkills = GetBool(L"server", L"AllowAirshipSkills", true);
	server.pledgeLoadTimeout = GetInt(L"server", L"PledgeLoadTimeout", 60);
	server.pledgeWarLoadTimeout = GetInt(L"server", L"PledgeWarLoadTimeout", 30);
	server.vitalityMultiplier = GetDouble(L"server", L"VitalityMultiplier", 1.0);
	server.loadDlls = GetString(L"server", L"LoadDlls", L"");

	voiceCommands.enabled = GetBool(L"voicecommands", L"Enabled", true);
	voiceCommands.expOnOff = GetBool(L"voicecommands", L"ExpOnOff", true);
	voiceCommands.online = GetBool(L"voicecommands", L"Online", true);
	voiceCommands.offline = GetBool(L"voicecommands", L"Offline", true);
	voiceCommands.time = GetBool(L"voicecommands", L"Time", true);

	fixes.maxReplenishedVitalityPoints = GetInt(L"fixes", L"MaxReplenishedVitalityPoints", 50);
}

void Config::Init()
{
	if (config) {
		return;
	}
	config = new Config(L"MyExt64.ini");
}

const wchar_t* Config::GetString(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue)
{
    static wchar_t buffer[16384];
	GetPrivateProfileString(section, name, defaultValue, buffer, sizeof(buffer), filename.c_str());
	return buffer;
}

INT64 Config::GetInt(const wchar_t *section, const wchar_t *name, const INT64 defaultValue)
{
	INT64 ret;
	std::wstring s;
	{
		std::wstringstream ss;
		ss << defaultValue;
		s = GetString(section, name, ss.str().c_str());
	}
	std::wstringstream ss;
	ss << s;
	ss >> ret;
	if (ss.fail()) {
		ret = defaultValue;
	}
	return ret;
}

bool Config::GetBool(const wchar_t *section, const wchar_t *name, const bool defaultValue)
{
	std::wstring s = GetString(section, name, L"");
	if (s == L"1" || s == L"true" || s == L"on" || s == L"yes") {
		return true;
	} else if (s == L"0" || s == L"false" || s == L"off" || s == L"no") {
		return false;
	} else {
		return defaultValue;
	}
}

double Config::GetDouble(const wchar_t *section, const wchar_t *name, const double defaultValue)
{
	double ret;
	std::wstring s;
	{
		std::wstringstream ss;
		ss << defaultValue;
		s = GetString(section, name, ss.str().c_str());
	}
	std::wstringstream ss;
	ss << s;
	ss >> ret;
	if (ss.fail()) {
		ret = defaultValue;
	}
	return ret;
}
