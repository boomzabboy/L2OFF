
#include <Server/Server.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/SkillEnchantOperator.h>
#include <Server/GraciaEpilogue.h>
#include <Server/DropRate.h>
#include <Server/EventDrop.h>
#include <Server/CNPC.h>
#include <Server/ShutdownChecker.h>
#include <Server/EnchantItem.h>
#include <Server/CMultiPartyCommandChannel.h>
#include <Server/CSummon.h>
#include <Server/BuilderCmd2Handler.h>
#include <Server/CHTMLCacheManager.h>
#include <Server/CSkillInfo.h>
#include <Server/CAttackAction.h>
#include <Server/COlympiadDefaultSetting.h>
#include <Server/OlympiadFixes.h>
#include <Server/AugmentationStatFix.h>
#include <Server/CMultiSellList.h>
#include <Common/Config.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <stdio.h>

int Server::protocolVersion = Server::ProtocolVersionGraciaFinal;
bool Server::debug = false;
CriticalSection Server::pledgeInitCS;
bool Server::pledgeInitialized = false;

void Server::Init()
{
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
	SetFixedPCCafePoints(Config::Instance()->server->fixedPCCafePoints);
	CUser::Init();
	CUserSocket::Init();
	SkillEnchantOperator::Init();
	if (GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		GraciaEpilogue::Init();
	}
	DropRate::Init();
	EventDrop::Init();
	CNPC::Init();
	ShutdownChecker::Init();
	EnchantItem::Init();
	CMultiPartyCommandChannel::Init();
	CSummon::Init();
	BuilderCmd2Handler::Init();
	CHTMLCacheManager::Init();
	CSkillInfo::Init();
	CAttackAction::Init();
	COlympiadDefaultSetting::Init();
	OlympiadFixes::Init();
	AugmentationStatFix::Init();
	CMultiSellList::Init();
	HideWarnings(); // call this at last!
}

void Server::Load()
{ GUARDED

	if (GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		GraciaEpilogue::Load();
	}
	EventDrop::Load();
	EnchantItem::Load();
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
	WriteMemoryBYTES(0x5EA1E2, "\x66\x31\xF6\x90\x90", 5);
	NOPMemory(0x6D323A, 5);
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
	return ::CreateWindowEx(dwExStyle, lpClassName, L"L2Server - patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void Server::StartHook(void *logger, int level, const wchar_t *fmt, const wchar_t *build)
{ GUARDED

	reinterpret_cast<void(*)(void*, int, const wchar_t*, const wchar_t*)>(0x6B9EBC)(logger, level, fmt, build);
	CLog::Add(CLog::Blue, L"Patched by MyExt64 (https://bitbucket.org/l2shrine/extender-public)");
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
	WriteMemoryDWORD(0xE5ABE8, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeWarTimeout));
	WriteMemoryDWORD(0xE5ABEC, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeOustPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF0, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeWithdrawPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF4, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeOustedPenaltyTimeout));
	WriteMemoryDWORD(0xE5ABF8, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeRechallengePenaltyTimeout));
	WriteMemoryDWORD(0xE5ABFC, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeRechallengeDespiteRejectionPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC00, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeDismissTimeout));
	WriteMemoryDWORD(0xE5AC04, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeDismissPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC08, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->pledgeDismissByNPC));
	WriteMemoryDWORD(0xE5AC00, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceCanAcceptNewMemberPledge));
	WriteMemoryDWORD(0xE5AC0C, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceOustPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC10, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceWithdrawPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC14, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceOustedPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC18, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceDismissPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC1C, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceRechallengePenaltyTimeout));
	WriteMemoryDWORD(0xE5AC20, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->allianceRechallengeDespiteRejectionPenaltyTimeout));
	WriteMemoryDWORD(0xE5AC24, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->castleAnnounceTime));
	WriteMemoryDWORD(0xE5AC28, reinterpret_cast<UINT32>(&Config::Instance()->clanRestrictions->castleStandbyTime));
}

void Server::ApplyMiscMXCFixes()
{
	WriteMemoryBYTE(0x55CDE9, 0x77); // fix condition x <= 0 -> x >= 0 in ressurection
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

