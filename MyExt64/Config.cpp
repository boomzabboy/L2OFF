
#include "Config.h"
#include "MyExt64.h"
#include <windows.h>
#include <sstream>

Config *Config::instance = 0;

Config::Config(const wchar_t *filename)
  : filename(filename),
    server(0),
	voiceCommands(0),
	fixes(0),
	rate(0)
{
	server = new Server(this);
	voiceCommands = new VoiceCommands(this);
	fixes = new Fixes(this);
	rate = new Rate(this);
}

Config::Server::Server(Config *config)
  : name(config->GetString(L"server", L"Name", L"Server")),
    protocolVersion(config->GetInt(L"server", L"ProtocolVersion", MyExt64::ProtocolVersionGraciaEpilogueUpdate1)),
	debug(config->GetBool(L"server", L"Debug", false)),
	maxIndex(config->GetInt(L"server", L"MaxIndex", 10000)),
	deadlockTimeout(config->GetInt(L"server", L"DeadlockTimeout", 300)),
	shutdownDuration(config->GetInt(L"server", L"ShutdownDuration", 180)),
	globalShout(config->GetBool(L"server", L"GlobalShout", false)),
	allowLoadNpcSettingsAnyTime(config->GetBool(L"server", L"AllowLoadNpcSettingsAnyTime", true)),
	mountKeepBuffs(config->GetBool(L"server", L"MountKeepBuffs", true)),
	dismountKeepBuffs(config->GetBool(L"server", L"DismountKeepBuffs", true)),
	allowAirshipSkills(config->GetBool(L"server", L"AllowAirshipSkills", true)),
	pledgeLoadTimeout(config->GetInt(L"server", L"PledgeLoadTimeout", 60)),
	pledgeWarLoadTimeout(config->GetInt(L"server", L"PledgeWarLoadTimeout", 30)),
	vitalityMultiplier(config->GetDouble(L"server", L"VitalityMultiplier", 1.0)),
	loadDlls(config->GetString(L"server", L"LoadDlls", L""))
{
}

Config::VoiceCommands::VoiceCommands(Config *config)
  : enabled(config->GetBool(L"voicecommands", L"Enabled", true)),
	expOnOff(config->GetBool(L"voicecommands", L"ExpOnOff", true)),
	online(config->GetBool(L"voicecommands", L"Online", true)),
	offline(config->GetBool(L"voicecommands", L"Offline", true)),
	time(config->GetBool(L"voicecommands", L"Time", true))
{
}

Config::Fixes::Fixes(Config *config)
  : maxReplenishedVitalityPoints(config->GetInt(L"fixes", L"MaxReplenishedVitalityPoints", 50)),
    commandChannelFriendly(config->GetBool(L"fixes", L"CommandChannelFriendly", true))
{
}

Config::Rate::Rate(Config *config)
  : adenaRate(config->GetDouble(L"rate", L"AdenaRate", 1.0)),
	dropRate(config->GetDouble(L"rate", L"DropRate", 1.0)),
	spoilRate(config->GetDouble(L"rate", L"SpoilRate", 1.0)),
	bossDropRate(config->GetDouble(L"rate", L"BossDropRate", 1.0)),
	herbRate(config->GetDouble(L"rate", L"HerbRate", 1.0)),
	fixupLowLevel(config->GetBool(L"rate", L"FixupLowLevel", false)),
	ignoredItems(config->GetIntSet(L"rate", L"IgnoredItems", std::set<INT64>())),
	dump(config->GetBool(L"rate", L"Dump", false))
{
}

Config* Config::Instance()
{
	if (!instance) {
		instance = new Config(L".\\MyExt64.ini");
	}
	return instance;
}

std::wstring Config::GetString(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue)
{
    static wchar_t buffer[16384];
	GetPrivateProfileString(section, name, defaultValue, buffer, sizeof(buffer), filename.c_str());
	return std::wstring(buffer);
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

std::set<INT64> Config::GetIntSet(const wchar_t *section, const wchar_t *name, const std::set<INT64> &defaultValue)
{
	std::wstring s(GetString(section, name, L""));
	if (s.empty()) {
		return defaultValue;
	}
	if (s == L"-" || s == L"null") {
		return std::set<INT64>();
	}
	std::set<INT64> result;
	std::wstring part;
	for (size_t i(0) ; i < s.size() ; ++i) {
		if (s[i] == L' ' || s[i] == L',' || s[i] == L';') {
			if (!part.empty()) {
				std::wstringstream ss;
				INT64 i;
				ss << part;
				ss >> i;
				result.insert(i);
				part.clear();
			}
		} else if (s[i] >= L'0' && s[i] <= L'9') {
			part.push_back(s[i]);
		}
	}
	if (!part.empty()) {
		std::wstringstream ss;
		INT64 i;
		ss << part;
		ss >> i;
		result.insert(i);
	}
	return result;
}

