
#include <Server/Server.h>
#include <Server/CIOBufferPool.h>
#include <Server/CWorld.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/SkillEnchantOperator.h>
#include <Server/GraciaFinal87.h>
#include <Server/GraciaEpilogue.h>
#include <Server/DropRate.h>
#include <Server/EventDrop.h>
#include <Server/CNPC.h>
#include <Server/ShutdownChecker.h>
#include <Server/EnchantItem.h>
#include <Server/CMultiPartyCommandChannel.h>
#include <Server/CCreature.h>
#include <Server/CSummon.h>
#include <Server/CPet.h>
#include <Server/BuilderCmd2Handler.h>
#include <Server/CHTMLCacheManager.h>
#include <Server/CSkillInfo.h>
#include <Server/CAttackAction.h>
#include <Server/COlympiadDefaultSetting.h>
#include <Server/OlympiadFixes.h>
#include <Server/AugmentationStatFix.h>
#include <Server/CMultiSellList.h>
#include <Server/CInstantZone.h>
#include <Server/SkillEnchantFix.h>
#include <Server/NpcServer.h>
#include <Server/CItem.h>
#include <Server/CSkillAction2.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Config.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <stdio.h>

int Server::protocolVersion = Server::ProtocolVersionGraciaFinal;
bool Server::debug = false;
CriticalSection Server::pledgeInitCS;
bool Server::pledgeInitialized = false;
Server::Plugin *Server::plugin = 0;

void Server::Init()
{
	CIOBufferPool<8192>::Init();
	CIOBufferPool<16384>::Init();
	SetProtocolVersion(Config::Instance()->server->protocolVersion);
	SetDebug(Config::Instance()->server->debug);
	SetMaxIndex(Config::Instance()->server->maxIndex);
	SetMaxLevel(Config::Instance()->server->maxLevelMain, Config::Instance()->server->maxLevelSubclass);
	DeadlockTimeout(Config::Instance()->server->deadlockTimeout * 1000 * 1000);
	DisableNoAuthExit();
	DisableSendMail();
	SetShutdownSeconds(Config::Instance()->server->shutdownDuration);
	EnableLoadNpcSettingsAnytime();
	AllowAirshipSkills();
	MountUnmountKeepBuffs();
	SetPledgeLoadTimeout(Config::Instance()->server->pledgeLoadTimeout);
	SetPledgeWarLoadTimeout(Config::Instance()->server->pledgeWarLoadTimeout);
	HookStart();
	HookLoad();
	HookOnLoadEnd();
	FixLoading();
	InitClanRestrictions();
	ApplyMiscMXCFixes();
	SetBuffSlots();
	if (Config::Instance()->fixes->relogKeepSongsDances) {
		RelogKeepSongsDances();
	}
	SetFixedPCCafePoints(Config::Instance()->server->fixedPCCafePoints);
	if (Config::Instance()->server->enableVitaminManager && Config::Instance()->server->enableVitaminManagerNonPremiumItems) {
		EnableVitaminManagerNonPremiumItems();
	}
	SetVitalityLevels();
	if (Config::Instance()->custom->removeKamaelRace) {
		RemoveKamaelRace();
	}
	CSharedCreatureData::InitServer();
	CWorld::Init();
	CUser::Init();
	CUserSocket::Init();
	SkillEnchantOperator::Init();
	if (GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		GraciaEpilogue::Init();
	} else if (GetProtocolVersion() == Server::ProtocolVersionGraciaFinalUpdate1) {
		GraciaFinal87::Init();
	}
	if (!Config::Instance()->server->plugin.empty()) {
		if (HMODULE mod = LoadLibrary(Config::Instance()->server->plugin.c_str())) {
			FARPROC proc = GetProcAddress(mod, "factory");
			if (proc) {
				plugin = reinterpret_cast<Plugin*(*)()>(proc)();
			} else {
				MessageBox(0, L"Can't load function factory from plugin", L"Error", 0);
				exit(1);
			}
		} else {
			MessageBox(0, L"Can't load plugin", L"Error", 0);
			exit(1);
		}
	}

	DropRate::Init();
	EventDrop::Init();
	CNPC::Init();
	ShutdownChecker::Init();
	EnchantItem::Init();
	CMultiPartyCommandChannel::Init();
	CCreature::Init();
	CSummon::Init();
	CPet::Init();
	BuilderCmd2Handler::Init();
	CHTMLCacheManager::Init();
	CSkillInfo::Init();
	CAttackAction::Init();
	COlympiadDefaultSetting::Init();
	OlympiadFixes::Init();
	AugmentationStatFix::Init();
	CMultiSellList::Init();
	CInstantZone::Init();
	NpcServer::Init();
	CItem::Init();
	CSkillAction2::Init();
	HideWarnings(); // call this at last!
}

void Server::ReloadConfig()
{
	Config::Instance()->Reload();
	DeadlockTimeout(Config::Instance()->server->deadlockTimeout * 1000 * 1000);
	SetMaxLevel(Config::Instance()->server->maxLevelMain, Config::Instance()->server->maxLevelSubclass);
	SetShutdownSeconds(Config::Instance()->server->shutdownDuration);
	SetPledgeLoadTimeout(Config::Instance()->server->pledgeLoadTimeout);
	SetPledgeWarLoadTimeout(Config::Instance()->server->pledgeWarLoadTimeout);
	InitClanRestrictions();
	SetBuffSlots();
	SetVitalityLevels();
	OlympiadFixes::SetEntryCounts();
}

void Server::Load()
{
	GUARDED;

	if (GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		GraciaEpilogue::Load();
	}
	EventDrop::Load();
	EnchantItem::Load();
	if (Config::Instance()->server->enableVitaminManager) {
		EnableVitaminManager();
	}
	FixPremiumBoost();
	OlympiadFixes::SetEntryCounts();
}

bool Server::IsDebug()
{
	return debug;
}

void Server::SetDebug(bool debug)
{
	Server::debug = debug;
}

int Server::GetProtocolVersion()
{
	return protocolVersion;
}

void Server::SetProtocolVersion(int version)
{
	char buffer[4];
	_snprintf_s(buffer, 4, "%d", version);
	WriteMemoryBYTES(0xC6BD83, buffer, strlen(buffer));
	protocolVersion = version;
}

void Server::SetMaxIndex(const size_t index)
{
	WriteMemoryDWORD(0x629E58, index - 1);
	WriteMemoryDWORD(0x643F3F, index - 1);
	WriteMemoryDWORD(0x6AE331, index - 1);
	WriteMemoryDWORD(0x7A76D9, index - 1);
	WriteMemoryDWORD(0x7A9AA3, index - 1);
	WriteMemoryDWORD(0xA268B3, index - 1);
	WriteMemoryDWORD(0x443D6B, index);
	WriteMemoryDWORD(0x5354A6, index);
	WriteMemoryDWORD(0x6AE4BD, index);
	WriteMemoryDWORD(0x71E052, index);
	WriteMemoryDWORD(0x763124, index);
	WriteMemoryDWORD(0x77C2B7, index);
	WriteMemoryDWORD(0x77CD45, index);
	WriteMemoryDWORD(0x77DC42, index);
	WriteMemoryDWORD(0x77DD45, index);
	WriteMemoryDWORD(0x7C7EF9, index);
	WriteMemoryDWORD(0x7C95D5, index);
	WriteMemoryDWORD(0x860E49, index);
	WriteMemoryDWORD(0x8619F1, index);
}

void Server::DeadlockTimeout(UINT32 timeout)
{
	WriteMemoryDWORD(0x690053, timeout);
}

void Server::DisableNoAuthExit()
{
	WriteInstructionJmp(0x6B27AC, 0x6B273B, 0x6B27FE);
}

void Server::DisableSendMail()
{
	NOPMemory(0x61BB2D, 5);
	NOPMemory(0x61CABA, 5);
}

void Server::HideWarnings()
{
	NOPMemory(0x42E44A, 5);
	NOPMemory(0x5EA1E2, 5);
	NOPMemory(0x6D323A, 5);
	NOPMemory(0x92DFEA, 5);
}

void Server::OnLoadEnd(UINT64 classBase)
{ GUARDED

	typedef UINT32 (__thiscall *t)(UINT64);
	t f = reinterpret_cast<t>(0x470544);
	int res = f(classBase);
	if (res == 0xF) {
		ShutdownChecker::StartChecking();
	}
}

void Server::SetShutdownSeconds(const int seconds)
{
	WriteMemoryDWORD(0x691402 + 3, static_cast<UINT32>(seconds));
}

void Server::EnableLoadNpcSettingsAnytime()
{
	if (Config::Instance()->server->allowLoadNpcSettingsAnyTime) {
		WriteMemoryBYTE(0x644DC5, 0x30);
	}
}

void Server::EnableGlobalShout()
{
	if (Config::Instance()->server->globalShout) {
		WriteMemoryBYTES(0x8abc3a, "\x31\xDB\x89\x5C\x24\x3C\x90", 7);
		WriteMemoryBYTES(0x8abc4a, "\x8D\x74\x24\xA0\x31\xFF", 6);
	}
	if (Config::Instance()->server->globalTrade) {
		WriteMemoryBYTES(0x8AC31E, "\x31\xDB\x89\x5C\x24\x68\x90", 7);
		WriteMemoryBYTES(0x8AC32C, "\x44\x8D\x77\xA0\x45\x31\xE4", 7);
	}
}

void Server::AllowAirshipSkills()
{
	if (Config::Instance()->server->allowAirshipSkills) {
		WriteMemoryBYTE(0x5310F3, 0x30);
	}
}

void Server::MountUnmountKeepBuffs()
{
	if (Config::Instance()->server->mountKeepBuffs) {
		NOPMemory(0x8FD944, 5);
	}
	if (Config::Instance()->server->dismountKeepBuffs) {
		NOPMemory(0x8FE172, 5);
	}
}

void Server::SetPledgeLoadTimeout(time_t timeout)
{
	WriteMemoryDWORD(0x7D8449 + 2, static_cast<UINT32>(max(10, min(timeout, 1800))));
}

void Server::SetPledgeWarLoadTimeout(time_t timeout)
{
	WriteMemoryBYTE(0x7D83FB + 3, static_cast<unsigned char>(max(10, min(timeout, 180)) - 6));
}

void Server::FixLoading()
{
	WriteInstructionCall(0x6B24B9, reinterpret_cast<UINT32>(CDominionInitDominion));
	WriteInstructionCall(0x6915D3, reinterpret_cast<UINT32>(CPledgeInitPledge));
	NOPMemory(0x7D853E, 5);
}

void Server::HookStart()
{
	WriteInstructionCall(0x6B354E, reinterpret_cast<UINT32>(StartHook));
	WriteInstructionCall(0x6B2C2F, reinterpret_cast<UINT32>(CreateWindowEx), 0x6B2C2F + 6);
}

HWND Server::CreateWindowEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	std::wstring name(lpWindowName);
	name += L" - patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)";
	return ::CreateWindowEx(dwExStyle, lpClassName, name.c_str(), dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void Server::StartHook(void *logger, int level, const wchar_t *fmt, const wchar_t *build)
{ GUARDED

	reinterpret_cast<void(*)(void*, int, const wchar_t*, const wchar_t*)>(0x6B9EBC)(logger, level, fmt, build);
	CLog::Add(CLog::Blue, L"Patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)");
	ShellExecute(0, L"open", L"cmd.exe", L"/C mkdir bak", 0, SW_HIDE);
	ShellExecute(0, L"open", L"cmd.exe", L"/C move LinError.txt.*.bak bak\\", 0, SW_HIDE);
}

void Server::HookLoad()
{
	WriteInstructionCall(0x6B1B71, reinterpret_cast<UINT32>(LoadHook));
}

void Server::LoadHook(void *x)
{ GUARDED

	reinterpret_cast<void(*)(void*)>(0x80E030)(x);
	Load();
}

void Server::HookOnLoadEnd()
{
	WriteInstructionCall(0x6B278A, reinterpret_cast<UINT32>(OnLoadEnd));
}

void __cdecl Server::CPledgeInitPledge()
{ GUARDED

	for (;;) {
		Sleep(100);
		ScopedLock lock(pledgeInitCS);
		if (pledgeInitialized) {
			break;
		}
	}
	reinterpret_cast<void(*)()>(0x5F4EAC)();
}

void __cdecl Server::CDominionInitDominion()
{ GUARDED

	reinterpret_cast<void(*)()>(0x5EA29C)();
	reinterpret_cast<void(*)()>(0x7D831C)();
	ScopedLock lock(pledgeInitCS);
	pledgeInitialized = true;
}

void Server::SetMaxLevel(const int main, const int subClass)
{
	WriteMemoryBYTE(0x562C8C, static_cast<const BYTE>(main));
	WriteMemoryBYTE(0x562C9E, static_cast<const BYTE>(subClass));
	WriteMemoryBYTE(0x4877C1, static_cast<const BYTE>(main - 1));
	WriteMemoryBYTE(0x7A620E, static_cast<const BYTE>(main - 1));
	const UINT64 *exp = reinterpret_cast<const UINT64*>(0xA77848);
	WriteMemoryQWORD(0x52C29A, exp[subClass + 1]);
	WriteMemoryQWORD(0x52C2A9, exp[subClass + 1] - 1);
}

void Server::InitClanRestrictions()
{
	WriteMemoryDWORD(0xE5ABE8, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeWarTimeout));
	WriteMemoryDWORD(0xE5ABEC, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeOustPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF0, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeWithdrawPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF4, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeOustedPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF8, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeRechallengePenaltyTimeout));
	WriteMemoryDWORD(0xE5ABFC, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeRechallengeDespiteRejectionPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC00, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeDismissTimeout));
	WriteMemoryDWORD(0xE5AC04, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeDismissPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC08, static_cast<UINT32>(Config::Instance()->clanRestrictions->pledgeDismissByNPC));
	WriteMemoryDWORD(0xE5AC00, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceCanAcceptNewMemberPledge));
	WriteMemoryDWORD(0xE5AC0C, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceOustPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC10, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceWithdrawPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC14, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceOustedPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC18, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceDismissPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC1C, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceRechallengePenaltyTimeout));
	WriteMemoryDWORD(0xE5AC20, static_cast<UINT32>(Config::Instance()->clanRestrictions->allianceRechallengeDespiteRejectionPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC24, static_cast<UINT32>(Config::Instance()->clanRestrictions->castleAnnounceTime));
	WriteMemoryDWORD(0xE5AC28, static_cast<UINT32>(Config::Instance()->clanRestrictions->castleStandbyTime));
}

void Server::ApplyMiscMXCFixes()
{
	WriteMemoryBYTE(0x55CDE9, 0x77); // fix condition x <= 0 -> x >= 0 in ressurection
	NOPMemory(0x7585FF, 20); // prevent possible crash on race condition
}

void Server::SetBuffSlots()
{
	WriteMemoryBYTE(0x56AFDA, Config::Instance()->buffSystem->maxSlots);
	WriteMemoryDWORD(0x840443, Config::Instance()->buffSystem->maxDivineInspirationBonusSlots);
}

void Server::SetFixedPCCafePoints(const INT32 points)
{
	if (points >= 0) {
		WriteMemoryBYTE(0x891E1E, 0xB9);
		WriteMemoryDWORD(0x891E1F, static_cast<UINT32>(points));
	}
}

void Server::EnableVitaminManager()
{
	WriteMemoryBYTE(0xF0C7FE, 0);
}

void Server::EnableVitaminManagerNonPremiumItems()
{
	WriteMemoryBYTE(0x8E147F, 0xEB);
}

void Server::SetVitalityLevels()
{
	// default is 240, 1800, 14600, 18200, 20000
	// epilogue is 240, 2000, 13000, 17000, 20000
	if (Config::Instance()->server->vitalityLevels.size() != 5) {
		return;
	}
	WriteMemoryDWORD(0x959697 + 2, Config::Instance()->server->vitalityLevels[0]);
	WriteMemoryDWORD(0x9596AB + 2, Config::Instance()->server->vitalityLevels[0]);
	WriteMemoryDWORD(0x9596B3 + 2, Config::Instance()->server->vitalityLevels[1]);
	WriteMemoryDWORD(0x9596CA + 2, Config::Instance()->server->vitalityLevels[1]);
	WriteMemoryDWORD(0x9596D2 + 2, Config::Instance()->server->vitalityLevels[2]);
	WriteMemoryDWORD(0x9596E9 + 2, Config::Instance()->server->vitalityLevels[2]);
	WriteMemoryDWORD(0x9596F1 + 2, Config::Instance()->server->vitalityLevels[3]);
	WriteMemoryDWORD(0x959708 + 2, Config::Instance()->server->vitalityLevels[3]);
	WriteMemoryDWORD(0x959710 + 2, Config::Instance()->server->vitalityLevels[4]);
	WriteMemoryDWORD(0x891DB0 + 1, Config::Instance()->server->vitalityLevels[4]);
}

Server::Plugin* Server::GetPlugin()
{
	return plugin;
}

void Server::RemoveKamaelRace()
{
	WriteMemoryBYTE(0x925297, 0x35);
	WriteMemoryBYTE(0x925288, 0x35);
}

void Server::RelogKeepSongsDances()
{
	WriteMemoryBYTE(0x8F9E3B, 0xF0);
}

void Server::FixPremiumBoost()
{
	for (size_t i = 0 ; i < 4 ; ++i) {
		UINT64 value = ReadMemoryQWORD(0xE53840 + i*8);
		*reinterpret_cast<double*>(&value) *= 0.01;
		WriteMemoryQWORD(0xE53840 + i*8, value);
	}
}

