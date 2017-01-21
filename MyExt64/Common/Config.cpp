
#include <Common/Config.h>
#include <Common/Utils.h>
#include <Server/Server.h>
#include <windows.h>
#include <fstream>
#include <sstream>

Config *Config::instance = 0;
CriticalSection Config::instanceCS;

Config::Config(const wchar_t *filename) :
	filename(filename),
	server(new Server),
	voiceCommands(new VoiceCommands),
	fixes(new Fixes),
	rate(new Rate),
	clanRestrictions(new ClanRestrictions),
	buffSystem(new BuffSystem),
	olympiad(new Olympiad),
	autoLoot(new AutoLoot),
	beta(new Beta),
	custom(new Custom),
	npcd(new Npcd)
{
	Reload();
}

void Config::Reload()
{
	server->Load(this);
	voiceCommands->Load(this);
	fixes->Load(this);
	rate->Load(this);
	clanRestrictions->Load(this);
	buffSystem->Load(this);
	olympiad->Load(this);
	autoLoot->Load(this);
	beta->Load(this);
	custom->Load(this);
	npcd->Load(this);
}

void Config::Server::Load(Config *config)
{
	name = config->GetString(L"server", L"Name", L"Server");
	protocolVersion = config->GetInt(L"server", L"ProtocolVersion", ::Server::ProtocolVersionGraciaEpilogueUpdate1);
	debug = config->GetBool(L"server", L"Debug", false);
	maxIndex = config->GetInt(L"server", L"MaxIndex", 10000);
	maxLevelMain = config->GetInt(L"server", L"MaxLevelMain", 85);
	maxLevelSubclass = config->GetInt(L"server", L"MaxLevelSubclass", 80);
	deadlockTimeout = config->GetInt(L"server", L"DeadlockTimeout", 300);
	shutdownDuration = config->GetInt(L"server", L"ShutdownDuration", 180);
	globalShout = config->GetBool(L"server", L"GlobalShout", false);
	globalTrade = config->GetBool(L"server", L"GlobalTrade", false);
	allowLoadNpcSettingsAnyTime = config->GetBool(L"server", L"AllowLoadNpcSettingsAnyTime", true);
	mountKeepBuffs = config->GetBool(L"server", L"MountKeepBuffs", true);
	dismountKeepBuffs = config->GetBool(L"server", L"DismountKeepBuffs", true);
	allowAirshipSkills = config->GetBool(L"server", L"AllowAirshipSkills", true);
	pledgeLoadTimeout = config->GetInt(L"server", L"PledgeLoadTimeout", 60);
	pledgeWarLoadTimeout = config->GetInt(L"server", L"PledgeWarLoadTimeout", 30);
	vitalityMultiplier = config->GetDouble(L"server", L"VitalityMultiplier", 1.0);
	vitalityLevels = config->GetIntList(L"server", L"VitalityLevels", std::vector<INT64>());
	fixedPCCafePoints = config->GetInt(L"server", L"FixedPCCafePoints", -1);
	enableVitaminManager = config->GetBool(L"server", L"EnableVitaminManager", false);
	enableVitaminManagerNonPremiumItems = config->GetBool(L"server", L"EnableVitaminManagerNonPremiumItems", false);
	oneScriptDirectory = config->GetBool(L"server", L"OneScriptDirectory", false);
	autoRemoveFromGMList = config->GetBool(L"server", L"AutoRemoveFromGMList", true);
	loadDlls = config->GetString(L"server", L"LoadDlls", L"");
	plugin = config->GetString(L"server", L"Plugin", L"");
	hookWriteProcessMemory = config->GetBool(L"server", L"HookWriteProcessMemory", false);
}

void Config::VoiceCommands::Load(Config *config)
{
	enabled = config->GetBool(L"voicecommands", L"Enabled", true);
	expOnOff = config->GetBool(L"voicecommands", L"ExpOnOff", true);
	petExpOnOff = config->GetBool(L"voicecommands", L"PetExpOnOff", true);
	online = config->GetBool(L"voicecommands", L"Online", true);
	offline = config->GetBool(L"voicecommands", L"Offline", true);
	time = config->GetBool(L"voicecommands", L"Time", true);
	autoloot = config->GetBool(L"voicecommands", L"Autoloot", true);
}

void Config::Fixes::Load(Config *config)
{
	maxReplenishedVitalityPoints = config->GetInt(L"fixes", L"MaxReplenishedVitalityPoints", 50);
	commandChannelFriendly = config->GetBool(L"fixes", L"CommandChannelFriendly", true);
	repeatSkillOnDistanceFailSeconds = config->GetInt(L"fixes", L"RepeatSkillOnDistanceFailSeconds", -1);
	disallowTradeInOlympiad = config->GetBool(L"fixes", L"DisallowTradeInOlympiad", true);
	relogKeepSongsDances = config->GetBool(L"fixes", L"RelogKeepSongsDances", true);
	fixSpiritshotLag = config->GetBool(L"fixes", L"FixSpiritshotLag", false);
	forceMonthlyOlympiad = config->GetBool(L"fixes", L"ForceMonthlyOlympiad", false);
	territoryWarPetFix = config->GetBool(L"fixes", L"TerritoryWarPetFix", true);
}

void Config::Rate::Load(Config *config)
{
	adenaRate = config->GetDouble(L"rate", L"AdenaRate", 1.0);
	dropRate = config->GetDouble(L"rate", L"DropRate", 1.0);
	spoilRate = config->GetDouble(L"rate", L"SpoilRate", 1.0);
	bossDropRate = config->GetDouble(L"rate", L"BossDropRate", 1.0);
	herbRate = config->GetDouble(L"rate", L"HerbRate", 1.0);
	fixupLowLevel = config->GetBool(L"rate", L"FixupLowLevel", false);
	ignoredItems = config->GetIntSet(L"rate", L"IgnoredItems", std::set<INT64>());
	dump = config->GetBool(L"rate", L"Dump", false);
}

void Config::ClanRestrictions::Load(Config *config)
{
	pledgeWarTimeout = config->GetInt(L"clan-restrictions", L"PledgeWarTimeout", 86400);
	pledgeOustPenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeOustPenaltyTimeout", 86400);
	pledgeWithdrawPenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeWithdrawPenaltyTimeout", 86400);
	pledgeOustedPenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeOustedPenaltyTimeout", 86400);
	pledgeRechallengePenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeRechallengePenaltyTimeout", 432000);
	pledgeRechallengeDespiteRejectionPenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeRechallengeDespiteRejectionPenaltyTimeout", 432000);
	pledgeDismissTimeout = config->GetInt(L"clan-restrictions", L"PledgeDismissTimeout", 604800);
	pledgeDismissPenaltyTimeout = config->GetInt(L"clan-restrictions", L"PledgeDismissPenaltyTimeout", 864000);
	pledgeDismissByNPC = config->GetInt(L"clan-restrictions", L"PledgeDismissByNPC", 604800);
	allianceCanAcceptNewMemberPledge = config->GetInt(L"clan-restrictions", L"AllianceCanAcceptNewMemberPledge", 604800);
	allianceOustPenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceOustPenaltyTimeout", 86400);
	allianceWithdrawPenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceWithdrawPenaltyTimeout", 86400);
	allianceOustedPenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceOustedPenaltyTimeout", 86400);
	allianceDismissPenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceDismissPenaltyTimeout", 86400);
	allianceRechallengePenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceRechallengePenaltyTimeout", 432000);
	allianceRechallengeDespiteRejectionPenaltyTimeout = config->GetInt(L"clan-restrictions", L"AllianceRechallengeDespiteRejectionPenaltyTimeout", 432000);
	castleAnnounceTime = config->GetInt(L"clan-restrictions", L"CastleAnnounceTime", 86400);
	castleStandbyTime = config->GetInt(L"clan-restrictions", L"CastleStandbyTime", 86400);
}

void Config::BuffSystem::Load(Config *config)
{
	maxSlots = config->GetInt(L"buff-system", L"MaxSlots", 20);
	maxDivineInspirationBonusSlots = config->GetInt(L"buff-system", L"MaxDivineInspirationBonusSlots", 4);
}

void Config::Olympiad::Load(Config *config)
{
	entryCountTeam = config->GetInt(L"olympiad", L"EntryCountTeam", 9);
	entryCountNonclass = config->GetInt(L"olympiad", L"EntryCountNonclass", 9);
	entryCountClass = config->GetInt(L"olympiad", L"EntryCountClass", 5);
}

void Config::AutoLoot::Load(Config *config)
{
	autoLootMobDrop = config->GetBool(L"autoloot", L"AutoLootMobDrop", false);
	autoLootBossDrop = config->GetBool(L"autoloot", L"AutoLootBossDrop", false);
	maximumAutoLootDistance = config->GetInt(L"autoloot", L"MaximumAutoLootDistance", 2000);
	excludedItems = config->GetIntSet(L"autoloot", L"ExcludedItems", std::set<INT64>());
}

void Config::Beta::Load(Config *config)
{
	enabled = config->GetBool(L"beta", L"Enabled", false);
	level = config->GetBool(L"beta", L"Level", false);
	class_ = config->GetBool(L"beta", L"Class", false);
	adena = config->GetBool(L"beta", L"Adena", false);
	noblesse = config->GetBool(L"beta", L"Noblesse", false);
	sp = config->GetBool(L"beta", L"Sp", false);
	fame = config->GetBool(L"beta", L"Fame", false);
}

void Config::Custom::Load(Config *config)
{
	removeKamaelRace = config->GetBool(L"custom", L"RemoveKamaelRace", false);
	removeVitalitySystem = config->GetBool(L"custom", L"RemoveVitalitySystem", false);
	ipBasedPremiumSystem = config->GetBool(L"custom", L"IPBasedPremiumSystem", false);
	ipBasedFixedPCCafePoints = config->GetInt(L"custom", L"IPBasedFixedPCCafePoints", -1);
	ipBasedPremiumSystemShowTime = config->GetBool(L"custom", L"IPBasedPremiumSystemShowTime", false);
	ipBasedPremiumSystemShowTimeSkillId = config->GetInt(L"custom", L"IPBasedPremiumSystemShowTimeSkillId", -1);
	minShopDistance = config->GetInt(L"custom", L"MinShopDistance", -1);
}

void Config::Npcd::Load(Config *config)
{
	useSplitAI = config->GetBool(L"npcd", L"UseSplitAI", false);
	aiBufferSizeMB = config->GetInt(L"npcd", L"AIBufferSizeMB", 512);
	dumpSplitAI = config->GetBool(L"npcd", L"DumpSplitAI", false);
}

Config* Config::Instance()
{
	const static char *paths[] = {
		".\\MyExt64.ini",
		"..\\MyExt64.ini",
		"..\\l2server\\MyExt64.ini",
		"..\\server\\MyExt64.ini",
		0};

	ScopedLock lock(instanceCS);
	if (instance) {
		return instance;
	}
	for (size_t i(0) ; paths[i] ; ++i) {
		if (std::ifstream(paths[i])) {
			instance = new Config(Widen(paths[i]).c_str());
			return instance;
		}
	}
	MessageBox(0,
		L"Can't find suitable config MyExt64.ini.\r\n\r\n"
		L"To use global config for all daemons, place it in top level directory (same level as Cached, NPC and L2Server directories)\r\n"
		L"To use local configs for single daemons, place it to daemon directory (Cached, NPC, L2Server)", L"ERROR", 0);
	exit(1);
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

std::vector<INT64> Config::GetIntList(const wchar_t *section, const wchar_t *name, const std::vector<INT64> &defaultValue)
{
	std::wstring s(GetString(section, name, L""));
	if (s.empty()) {
		return defaultValue;
	}
	std::vector<INT64> result;
	if (s == L"-" || s == L"null") {
		return result;
	}
	std::wstring part;
	for (size_t i(0) ; i < s.size() ; ++i) {
		if (s[i] == L' ' || s[i] == L',' || s[i] == L';') {
			if (!part.empty()) {
				std::wstringstream ss;
				INT64 i;
				ss << part;
				ss >> i;
				result.push_back(i);
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
		result.push_back(i);
	}
	return result;
}

std::set<INT64> Config::GetIntSet(const wchar_t *section, const wchar_t *name, const std::set<INT64> &defaultValue)
{
	std::wstring s(GetString(section, name, L""));
	if (s.empty()) {
		return defaultValue;
	}
	std::set<INT64> result;
	if (s == L"-" || s == L"null") {
		return result;
	}
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

