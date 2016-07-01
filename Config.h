
#pragma once

#include <string>
#include <windows.h>

class Config {
public:
	static void Init();

	struct {
		std::wstring name;
		int protocolVersion;
		bool debug;
		size_t maxIndex;
		time_t deadlockTimeout;
		time_t shutdownDuration;
		bool globalShout;
		bool allowLoadNpcSettingsAnyTime;
		bool mountKeepBuffs;
		bool dismountKeepBuffs;
		bool allowAirshipSkills;
		time_t pledgeLoadTimeout;
		time_t pledgeWarLoadTimeout;
		double vitalityMultiplier;
		std::wstring loadDlls;
	} server;

	struct {
		bool enabled;
		bool expOnOff;
		bool online;
		bool offline;
		bool time;
	} voiceCommands;

	struct {
		int maxReplenishedVitalityPoints;
	} fixes;

protected:
	Config(const wchar_t *filename);
	const wchar_t* GetString(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue);
	INT64 GetInt(const wchar_t *section, const wchar_t *name, const INT64 defaultValue);
	bool GetBool(const wchar_t *section, const wchar_t *name, const bool defaultValue);
	double GetDouble(const wchar_t *section, const wchar_t *name, const double defaultValue);

	std::wstring filename;
};

extern Config *config;

