
#pragma once

#include <string>
#include <set>
#include <vector>
#include <windows.h>
#include <Common/CriticalSection.h>

class Config {
public:
	static Config* Instance();
	void Reload();

	struct Server {
		void Load(Config *config);

		std::wstring name;
		int protocolVersion;
		bool debug;
		size_t maxIndex;
		size_t maxLevelMain;
		size_t maxLevelSubclass;
		time_t deadlockTimeout;
		time_t shutdownDuration;
		bool globalShout;
		bool globalTrade;
		bool allowLoadNpcSettingsAnyTime;
		bool mountKeepBuffs;
		bool dismountKeepBuffs;
		bool allowAirshipSkills;
		time_t pledgeLoadTimeout;
		time_t pledgeWarLoadTimeout;
		double vitalityMultiplier;
		std::vector<INT64> vitalityLevels;
		INT32 fixedPCCafePoints;
		bool enableVitaminManager;
		bool enableVitaminManagerNonPremiumItems;
		bool oneScriptDirectory;
		bool autoRemoveFromGMList;
		std::wstring loadDlls;
		std::wstring plugin;
		bool hookWriteProcessMemory;
	} *server;

	struct VoiceCommands {
		void Load(Config *config);

		bool enabled;
		bool expOnOff;
		bool petExpOnOff;
		bool online;
		bool offline;
		bool time;
		bool autoloot;
	} *voiceCommands;

	struct Fixes {
		void Load(Config *config);

		int maxReplenishedVitalityPoints;
		bool commandChannelFriendly;
		int repeatSkillOnDistanceFailSeconds;
		bool disallowTradeInOlympiad;
		bool relogKeepSongsDances;
		bool fixSpiritshotLag;
		bool forceMonthlyOlympiad;
		bool territoryWarPetFix;
	} *fixes;

	struct Rate {
		void Load(Config *config);

		double adenaRate;
		double dropRate;
		double spoilRate;
		double bossDropRate;
		double herbRate;
		bool fixupLowLevel;
		std::set<INT64> ignoredItems;
		bool dump;
	} *rate;

	struct ClanRestrictions {
		void Load(Config *config);

		UINT32 pledgeWarTimeout;
		UINT32 pledgeOustPenaltyTimeout;
		UINT32 pledgeWithdrawPenaltyTimeout;
		UINT32 pledgeOustedPenaltyTimeout;
		UINT32 pledgeRechallengePenaltyTimeout;
		UINT32 pledgeRechallengeDespiteRejectionPenaltyTimeout;
		UINT32 pledgeDismissTimeout;
		UINT32 pledgeDismissPenaltyTimeout;
		UINT32 pledgeDismissByNPC;
		UINT32 allianceCanAcceptNewMemberPledge;
		UINT32 allianceOustPenaltyTimeout;
		UINT32 allianceWithdrawPenaltyTimeout;
		UINT32 allianceOustedPenaltyTimeout;
		UINT32 allianceDismissPenaltyTimeout;
		UINT32 allianceRechallengePenaltyTimeout;
		UINT32 allianceRechallengeDespiteRejectionPenaltyTimeout;
		UINT32 castleAnnounceTime;
		UINT32 castleStandbyTime;
	} *clanRestrictions;

	struct BuffSystem {
		void Load(Config *config);

		int maxSlots;
		int maxDivineInspirationBonusSlots;
	} *buffSystem;

	struct Olympiad {
		void Load(Config *config);

		int entryCountTeam;
		int entryCountNonclass;
		int entryCountClass;
	} *olympiad;

	struct AutoLoot {
		void Load(Config *config);

		bool autoLootMobDrop;
		bool autoLootBossDrop;
		int maximumAutoLootDistance;
		std::set<INT64> excludedItems;
	} *autoLoot;

	struct Beta {
		void Load(Config *config);

		bool enabled;
		bool level;
		bool class_;
		bool adena;
		bool noblesse;
		bool sp;
		bool fame;
	} *beta;

	struct Custom {
		void Load(Config *config);

		bool removeKamaelRace;
		bool removeVitalitySystem;

		bool ipBasedPremiumSystem;
		int ipBasedFixedPCCafePoints;
		bool ipBasedPremiumSystemShowTime;
		int ipBasedPremiumSystemShowTimeSkillId;

		int minShopDistance;
	} *custom;

	struct Npcd {
		void Load(Config *config);

		bool useSplitAI;
		size_t aiBufferSizeMB;
		bool dumpSplitAI;
	} *npcd;

	struct Misc {
		void Load(Config *config);

		bool offlineTradeChangeNameColor;
	} *misc;

protected:
	Config(const wchar_t *filename);
	std::wstring GetString(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue);
	INT64 GetInt(const wchar_t *section, const wchar_t *name, const INT64 defaultValue);
	bool GetBool(const wchar_t *section, const wchar_t *name, const bool defaultValue);
	double GetDouble(const wchar_t *section, const wchar_t *name, const double defaultValue);
	std::vector<INT64> GetIntList(const wchar_t *section, const wchar_t *name, const std::vector<INT64> &defaultValue);
	std::set<INT64> GetIntSet(const wchar_t *section, const wchar_t *name, const std::set<INT64> &defaultValue);

	std::wstring filename;
	static Config *instance;
	static CriticalSection instanceCS;
};

