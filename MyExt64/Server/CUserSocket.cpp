
#include <Server/CUserSocket.h>
#include <Server/CUser.h>
#include <Server/Server.h>
#include <Server/GraciaEpilogue.h>
#include <Server/CParty.h>
#include <Server/CMultiPartyCommandChannel.h>
#include <Server/CTradeManager.h>
#include <Server/CTrade.h>
#include <Server/SkillEnchantFix.h>
#include <Server/Beta.h>
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/SmartPtr.h>
#include <Common/CSharedCreatureData.h>
#include <new>
#include <sstream>
#include <time.h>

CUserSocket::PacketHandler *CUserSocket::exHandlers = reinterpret_cast<CUserSocket::PacketHandler*>(0x121C0D60);
void *CUserSocket::offlineTradeVtable[0x16];

static WORD maxOpcodeEx = 0x68;

CUserSocket::IgnorePacket::IgnorePacket(const wchar_t *format, ...)
{
	if (Server::IsDebug()) {
		va_list va;
		va_start(va, format);
		CLog::AddV(CLog::Red, format, va);
		va_end(va);
	}
}

namespace {

void ReplaceOutExOpcode(unsigned int address, BYTE opcode)
{
	WriteMemoryBYTE(address + 2, static_cast<BYTE>(opcode));
	WriteMemoryBYTE(address + 9, static_cast<BYTE>(0xFE - opcode));
}

}

void CUserSocket::Init()
{
	WriteMemoryDWORD(0x91BFEE, sizeof(CUserSocket));
	WriteMemoryDWORD(0x93CEC1, sizeof(CUserSocket));
	WriteInstruction(0x93CEDC, reinterpret_cast<UINT32>(Constructor), 0xE8);
	WriteInstruction(0x92E068, reinterpret_cast<UINT32>(Destructor), 0xE8);
	WriteMemoryQWORD(0x92EAE0, 0x8B48D38B49C28B44);
	WriteMemoryQWORD(0x92EAE8, 0x98248489482024CB);
	WriteInstructionCallJmpEax(0x92EF0B, reinterpret_cast<UINT32>(OutGamePacketHandlerWrapper), 0x92EF17);
	WriteInstructionCallJmpEax(0x92EDFE, reinterpret_cast<UINT32>(InGamePacketHandlerWrapper), 0x92EE0C);
	WriteInstructionCall(0x92EAE9, reinterpret_cast<UINT32>(InGamePacketExHandlerWrapper), 0x92EB03);

	const static char *packetDecryptHelperBuffer = \
		/* 0x00 */ "\x48\x89\xF2"           // mov rdx, rsi
		/* 0x03 */ "\x90\x90\x90\x90\x90"   // placeholder for jmp
		/* 0x08 */ ;
	WriteInstructionJmp(reinterpret_cast<UINT32>(&packetDecryptHelperBuffer[0x03]), reinterpret_cast<UINT32>(PacketDecryptWrapper));
	WriteInstructionCall(0x92ECA2, reinterpret_cast<UINT32>(packetDecryptHelperBuffer));
	MakeExecutable(reinterpret_cast<UINT32>(packetDecryptHelperBuffer), 0x8);
	NOPMemory(0x92EC93, 2);

	switch (Server::GetProtocolVersion()) {
	case Server::ProtocolVersionGraciaFinal:
	case Server::ProtocolVersionGraciaFinalUpdate1:
		maxOpcodeEx = 0x68;
		break;
	case Server::ProtocolVersionGraciaEpilogue:
		maxOpcodeEx = 0x7D;
		break;
	case Server::ProtocolVersionGraciaEpilogueUpdate1:
		maxOpcodeEx = 0x80;
		break;
	default:
		maxOpcodeEx = 0x68;
		break;
	}

	WriteMemoryBYTES(0x5D4FA7, "\x80\xFB", 2);
	WriteMemoryBYTES(0x5D4FAE, "\x75\xE3", 2);
	WriteMemoryBYTE(0x5D4FA9, maxOpcodeEx + 1);
	WriteMemoryBYTE(0x92EAC6, maxOpcodeEx + 1);

	if (Server::GetProtocolVersion() == Server::ProtocolVersionGraciaFinalUpdate1) {
		ReplaceOutExOpcode(0x7ED0D8, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED213, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED3DB, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED537, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDA07, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDF2F, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x47613C, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x476383, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x915BE1, 0xA9); // FE:A8 -> FE:A9
		ReplaceOutExOpcode(0x5AB7D2, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x5ABD02, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE2EB, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE44F, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE6EA, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE8CD, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x9124B5, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x912545, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x91257A, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x485364, 0xAB); // FE:AA -> FE:AB
		ReplaceOutExOpcode(0x971667, 0xAB); // FE:AA -> FE:AB
		ReplaceOutExOpcode(0x8CFBC3, 0xAD); // FE:AB -> FE:AD
	}
	if (Server::GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		// server packets:
		ReplaceOutExOpcode(0x7ED0D8, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED213, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED3DB, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED537, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7EDA07, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7EDF2F, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x47613C, 0xB9); // FE:A7 -> FE:B9
		ReplaceOutExOpcode(0x476383, 0xB9); // FE:A7 -> FE:B9
		ReplaceOutExOpcode(0x915BE1, 0xBA); // FE:A8 -> FE:BA
		ReplaceOutExOpcode(0x5AB7D2, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x5ABD02, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE2EB, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE44F, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE6EA, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE8CD, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x9124B5, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x912545, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x91257A, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x485364, 0xBC); // FE:AA -> FE:BC
		ReplaceOutExOpcode(0x971667, 0xBC); // FE:AA -> FE:BC
		ReplaceOutExOpcode(0x8CFBC3, 0xBD); // FE:AB -> FE:BD
		ReplaceOutExOpcode(0x8ADEB8, 0xBE); // FE:AC -> FE:BE
		WriteMemoryBYTE(0x8ADEF8, 0xBE); // FE:AC -> FE:BE
	}

	WriteMemoryQWORD(0xc74720, reinterpret_cast<UINT64>(SendWrapper));

	memcpy(reinterpret_cast<void*>(offlineTradeVtable), reinterpret_cast<void*>(0xC746B8), sizeof(offlineTradeVtable));
	offlineTradeVtable[0x04] = reinterpret_cast<void*>(OfflineTradeDummyTimerExpired);
	offlineTradeVtable[0x0D] = reinterpret_cast<void*>(OfflineTradeDummySend);
	offlineTradeVtable[0x0E] = reinterpret_cast<void*>(OfflineTradeDummySendV);
	offlineTradeVtable[0x10] = reinterpret_cast<void*>(OfflineTradeDummyOnClose);
	offlineTradeVtable[0x11] = reinterpret_cast<void*>(OfflineTradeDummyOnRead);
	WriteInstructionCall(0x4D5E01, reinterpret_cast<UINT32>(CloseWrapperKick));
	WriteInstructionCall(0x5E1B30, reinterpret_cast<UINT32>(BindUserWrapper));
	WriteMemoryDWORD(0x975586 + 0x3, offsetof(CUserSocket, ext) + offsetof(Ext, offlineSocketHandleCopy)); // user report socket handle
	WriteInstructionCall(0x459F50+0x1E7, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x459F50+0x36F, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x92CA6C+0x3BF, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x92CA6C+0x538, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x92CA6C+0x640, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x95BC18+0xFA0, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x95D6B4+0xE1B, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x95F6E0+0x835, reinterpret_cast<UINT32>(KickOfflineWrapper));
	WriteInstructionCall(0x9602C8+0x968, reinterpret_cast<UINT32>(KickOfflineWrapper));

	WriteMemoryBYTES(0x93F892, "\x48\x8B\xCE", 3); // mov rcx, rsi (CUserSocket*)
	WriteInstructionCall(0x93F895, reinterpret_cast<UINT32>(CheckCharacterNameWrapper));
	WriteMemoryBYTES(0x93F89A, // cmp al, 0 + apropriate jumps
		"\x3C\x00\x75\x09\x48\xC7\xC0\xEE"
		"\xF8\x93\x00\xFF\xE0\x48\xC7\xC0"
		"\xE5\xF8\x93\x00\xFF\xE0", 0x16);

	WriteMemoryBYTES(0x933A5E,
		"\x41\x89\xC8"      // mov r8d, ecx (const UINT32 protocolVersion)
		"\x48\x89\xC2"      // mov rdx, rax (const BYTE *packet)
		"\x48\x89\xF9", 9); // mov rcx, rdi (CUserSocket *self)
	WriteInstructionCall(0x933A67, reinterpret_cast<UINT32>(ProtocolVersionPacketWrapper));
	WriteMemoryBYTES(0x933A6C,
		"\x31\xDB"      // xor ebx, ebx
		"\xFF\xE0", 4); // jmp eax

	WriteMemoryQWORD(0xE5FC78, reinterpret_cast<UINT64>(HtmlCmdObserverWrapper));

	WriteAddress(0xA2D92F, reinterpret_cast<UINT32>(TradeAddItemsPacketWrapper));

	WriteInstructionCall(0x8AF9B8, reinterpret_cast<UINT32>(SendSendAbnormalStatusInfoWrapper));

	WriteMemoryBYTES(0x912880, "\x30\xC0", 2); // DummyPacket not to disconnect user

	WriteMemoryQWORD(0xB9C2C8, reinterpret_cast<UINT64>(SendVWrapper));
	WriteMemoryQWORD(0xC29AF8, reinterpret_cast<UINT64>(SendVWrapper));
	WriteMemoryQWORD(0xC74728, reinterpret_cast<UINT64>(SendVWrapper));
}

CUserSocket* __cdecl CUserSocket::Constructor(CUserSocket *self, SOCKET s)
{ GUARDED

	CUserSocket *ret = reinterpret_cast<CUserSocket*(*)(CUserSocket*, SOCKET)>(0x93CADC)(self, s);
	new (&ret->ext) Ext();
	return ret;
}

CUserSocket* __cdecl CUserSocket::Destructor(CUserSocket *self, bool isMemoryFreeUsed)
{ GUARDED

	self->ext.~Ext();
	return reinterpret_cast<CUserSocket*(*)(CUserSocket*, bool)>(0x92DE7C)(self, isMemoryFreeUsed);
}

CUserSocket::Ext::Ext() :
	offlineUser(0),
	offlineSocketHandleCopy(0)
{
	if (Server::GetPlugin()) {
		Server::GetPlugin()->init(pluginData, pluginCS);
	}
}

CUserSocket::Ext::~Ext()
{
}

void CUserSocket::IncRef(const char *file, const int line)
{
	reinterpret_cast<void(*)(CUserSocket*, const char*, int, int)>(
		(*reinterpret_cast<UINT64**>(this))[1])(this, file, line, 1);
}

void CUserSocket::DecRef(const char *file, const int line)
{
	reinterpret_cast<void(*)(CUserSocket*, const char*, int, int)>(
		(*reinterpret_cast<UINT64**>(this))[2])(this, file, line, 1);
}

CUser* CUserSocket::GetUser()
{
	return user;
}

void CUserSocket::Send(const char *format, ...)
{ GUARDED

	va_list va;
	va_start(va, format);
	SendV(format, va);
	va_end(va);
}

void CUserSocket::SendVWrapper(CUserSocket* self, const char *format, va_list va)
{
	self->SendV(format, va);
}

void CUserSocket::SendV(const char *format, va_list va)
{
	if (!this) {
		CLog::Add(CLog::Red, L"Attempt to write to null socket!");
		return;
	}
	reinterpret_cast<void(*)(CUserSocket*, const char*, va_list)>(0x859934)(this, format, va);
}

void CUserSocket::SendSystemMessage(UINT32 id)
{
	reinterpret_cast<void(*)(CUserSocket*, UINT32)>(0x40D10C)(this, id);
}

void CUserSocket::SendSystemMessage(const wchar_t *sender, const wchar_t *message)
{
	reinterpret_cast<void(*)(CUserSocket*, const wchar_t*, const wchar_t*)>(0x9244F0)(this, sender, message);
}

void CUserSocket::SendSystemMessageFmt(const wchar_t *sender, const wchar_t *format, ...)
{
	va_list args;
	wchar_t buffer[4096];
	va_start (args, format);
	vswprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]), format, args);
	va_end(args);
	SendSystemMessage(sender, buffer);
}

void CUserSocket::Close()
{
	GUARDED;

	//status = 2;
	*reinterpret_cast<UINT32*>(&reinterpret_cast<char*>(this)[0x570]) = 6;
	reinterpret_cast<void(*)(CUserSocket*)>(0x4564D8)(this);
}

void CUserSocket::OnClose()
{
	reinterpret_cast<void(*)(CUserSocket*)>(0x93E5E0)(this);
}

void __cdecl CUserSocket::SendWrapper(CUserSocket *self, const char *format, ...)
{ GUARDED

	va_list args;
    va_start(args, format);

	if (!self->user) {
		self->SendV(format, args);
		va_end(args);
		return;
	}

	UINT64 *p = reinterpret_cast<UINT64*>(args);
	std::string f = format;
	BYTE o = *reinterpret_cast<BYTE*>(&p[0]);

	if (f == "cdddQdd" && o == 0x62 && p[1] == 0x5F && self->user->ext.isExpOff) {
		*reinterpret_cast<UINT32*>(&p[4]) = 0;
	}

	if (f == "cd" && o == 0x7C) {
		CUser *user_ = self->user;
		if (user_) {
			user_->ext.guard.isEnchanting = true;
		}
	}

	if (Config::Instance()->fixes->commandChannelFriendly) {
		CUser *user = self->user;
		if (user) {
			CParty *party = user->GetParty();
			if (party && party->GetMaster() == user) {
				if (f == "cdd" && o == 0x62) {
					switch (p[1]) {
					case 0x62e: // you have joined the command channel
						{
							CMultiPartyCommandChannel *channel = user->GetMPCC();
							if (channel) {
								channel->SendRelationUpdates();
							}
						}
						break;
					case 0x62f: // you were dismissed from the command channel
					case 0x632: // you have quit the command channel
						party->SendRelationChanged();
						break;
					default:
						break;
					}
				} else if (f == "cdddS" && o == 0x62) {
					switch (p[1]) {
					case 0x630: // %s's party has been dismissed
					case 0x633: // %s's party has left the Command Channel.
						{
							CMultiPartyCommandChannel *channel = user->GetMPCC();
							if (channel) {
								channel->SendRelationUpdates();
							} else {
								party->SendRelationChanged();
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}

	self->SendV(format, args);
	va_end(args);
}

void __cdecl CUserSocket::OfflineTradeDummyTimerExpired(CUserSocket*, int)
{
}

void __cdecl CUserSocket::OfflineTradeDummySend(CUserSocket*, const char*, ...)
{
}

void __cdecl CUserSocket::OfflineTradeDummySendV(CUserSocket*, const char*, va_list)
{
}

void __cdecl CUserSocket::OfflineTradeDummyOnClose(CUserSocket*)
{
}

void __cdecl CUserSocket::OfflineTradeDummyOnRead(CUserSocket*)
{
}

void __cdecl CUserSocket::CloseWrapperKick(CUserSocket *self)
{
	CUser *user = self->ext.offlineUser;
	self->ext.offlineUser = 0;
	if (user) {
		self->user = user;
		self->OnClose();
		self->DecRef(__FILE__, __LINE__);
	} else {
		self->Close();
	}
}

void __cdecl CUserSocket::BindUserWrapper(CUserSocket *self, CUser *user)
{
	self->BindUser(user);
}

void CUserSocket::BindUser(CUser *user)
{
	GUARDED;

	if (!user || (Config::Instance()->custom->removeKamaelRace && user->sd->race > 4)) {
		Close();
		return;
	}

	ext.offlineSocketHandleCopy = socketHandleCopy;
	return reinterpret_cast<void(*)(CUserSocket*, CUser*)>(0x9246DC)(this, user);
}

void __cdecl CUserSocket::KickOfflineWrapper(CUserSocket *self)
{
	GUARDED;

	if (!self) {
		return;
	}
	ScopedLock lock(self->ext.offlineCS);
	CUser *user = self->ext.offlineUser;
	if (user) {
		self->ext.offlineUser = 0;
		self->user = user;
		lock.Release();
		self->OnClose();
		self->DecRef(__FILE__, __LINE__);
	} else {
		lock.Release();
		reinterpret_cast<void(*)(CUserSocket*)>(0x456738)(self);
    }
}

bool CUserSocket::CheckCharacterNameWrapper(CUserSocket *self, const wchar_t *name)
{
	return self->CheckCharacterName(name);
}

bool CUserSocket::CheckCharacterName(const wchar_t *name)
{ GUARDED

	std::wstring name_(name);
	if (name_.empty() || name_.size() >= 15) {
		return false;
	}
	for (std::wstring::const_iterator i(name_.begin()) ; i != name_.end() ; ++i) {
		if ((*i < 'A' || *i > 'Z')
			&& (*i < 'a' || *i > 'z')
			&& (*i < '0' || *i > '9')) {

			return false;
		}
	}
	return true;
}

UINT64 __cdecl CUserSocket::ProtocolVersionPacketWrapper(CUserSocket *self, const BYTE *packet, const UINT32 protocolId, BYTE *buff)
{
	return self->ProtocolVersionPacket(packet, protocolId, buff);
}

UINT64 CUserSocket::ProtocolVersionPacket(const BYTE *packet, const UINT32 protocolId, BYTE *buff)
{ GUARDED

	if (*reinterpret_cast<const UINT16*>(packet - 7) != 267) {
		CLog::Add(CLog::Red, L"Client %s: Invalid packet length (%d, expected %d)",
			GetIP().c_str(), *reinterpret_cast<const UINT16*>(packet - 7), 267);
		return 0x933B2F; // close connection
	}

	UINT32 clientCRC = 0;
	Disassemble(packet, "bd", 0x100, buff, &clientCRC);

	if (protocolId != Server::GetProtocolVersion()) {
		CLog::Add(CLog::Red, L"Client %s: Invalid client protocol (%d, expected %d)",
			GetIP().c_str(), protocolId, Server::GetProtocolVersion());
		return 0x933A9C; // fail
	}

	if (memcmp(buff, reinterpret_cast<const void*>(0x121C1360), 0x100)) {
		CLog::Add(CLog::Red, L"Client %s: Invalid key block", GetIP().c_str());
		return 0x933A9C; // fail
	}

	UINT32 serverCRC = 0;
	switch (Server::GetProtocolVersion()){
		case Server::ProtocolVersionGraciaFinal: serverCRC = 0x601F5D11; break;
		case Server::ProtocolVersionGraciaFinalUpdate1: serverCRC = 0; break; // unknown by now
		case Server::ProtocolVersionGraciaEpilogue: serverCRC = 0; break; // unknown by now
		case Server::ProtocolVersionGraciaEpilogueUpdate1: serverCRC = 0xFEF423A6; break;
		default: serverCRC = 0; break;
	};

	if (serverCRC && serverCRC != clientCRC) {
		CLog::Add(CLog::Red, L"Client %s: Invalid CRC (%x, expected %x)",
			GetIP().c_str(), clientCRC, serverCRC);
		return 0x933B2F; // close connection
	}

	return 0x933B5D; // ok
}

std::wstring CUserSocket::GetIP()
{
	std::wstringstream ws;
	ws << static_cast<int>(clientIP.S_un.S_un_b.s_b1)
		<< "." << static_cast<int>(clientIP.S_un.S_un_b.s_b1)
		<< "." << static_cast<int>(clientIP.S_un.S_un_b.s_b2)
		<< "." << static_cast<int>(clientIP.S_un.S_un_b.s_b3);
	return ws.str();
}

bool __cdecl CUserSocket::HtmlCmdObserverWrapper(CUserSocket *self, CUser *user, const wchar_t *s1, const wchar_t *s2)
{
	return self->HtmlCmdObserver(user, s1, s2);
}

bool CUserSocket::HtmlCmdObserver(CUser *user, const wchar_t *s1, const wchar_t *s2)
{ GUARDED

	if (user->IsNowTrade()) {
		return false;
	}
	return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*, const wchar_t*)>(0x948444)(this, user, s1, s2);
}

bool __cdecl CUserSocket::TradeAddItemsPacketWrapper(CUserSocket *socket, const BYTE *packet)
{
	GUARDED;

	CUser *user = socket->user;
	if (!user) {
		return false;
	}
	if (!user->IsNowTrade()) {
		return false;
	}
	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x91C998)(socket, packet);
}

bool __cdecl CUserSocket::LinkHtmlPacketWrapper(CUserSocket *socket, const BYTE *packet)
{
	GUARDED;

	wchar_t buffer[0x800];
	Disassemble(packet, "S", sizeof(buffer) / sizeof(buffer[0]), buffer);

	std::wstring link(buffer);

	if (link.find(L"..") != std::wstring::npos) {
		return false;
	}

	size_t pos = link.rfind(L"#");
	if (pos != std::wstring::npos) {
		link = link.substr(0, pos);
	}

	pos = link.rfind(L".");
	if (pos == std::wstring::npos) {
		return false;
	}

	std::wstring extension = link.substr(pos + 1);
	if (extension != L"htm" && extension != L"html") {
		return false;
	}

	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x94A098)(socket, packet);
}

void CUserSocket::SetGuard(UINT32 &i)
{
	CUser *user_ = user;
	if (user_) {
		i = GetTickCount() + 2000;
	}
}

void CUserSocket::CheckGuard(const UINT32 &i) const
{
	CUser *user_ = user;
	if (!user_ || i >= GetTickCount()) {
		throw IgnorePacket(L"CheckGuard prevented packet");
	}
}

void __cdecl CUserSocket::PacketDecryptWrapper(unsigned char *data, CUserSocket *socket, UINT32 size)
{
	if (reinterpret_cast<unsigned char*>(socket)[0xDC]) {
		reinterpret_cast<void(*)(unsigned char*, UINT64, UINT32)>(0x91C148)(
			data, reinterpret_cast<UINT64>(socket) + 0xDC, size);
	}

	if (Server::GetPlugin()) {
		BYTE opcode = data[0];
		if (opcode <= 0xD0) {
			opcode = (*reinterpret_cast<UINT32**>(reinterpret_cast<char*>(socket) + 0xF10))[opcode];
		} else {
			opcode = 0xD1;
		}
		Server::GetPlugin()->decrypt(
			socket->ext.pluginData, socket->ext.pluginCS, data+1, size+2, opcode);
	}
}

void CUserSocket::CheckTargetInHide(const unsigned char *packet, const size_t offset)
{
	CUser *user_ = user;
	if (!user_) {
		throw IgnorePacket(L"Packet without user");
	}
	UINT32 objectId = user_->objectId;
	UINT32 targetId = user_->targetId;
	if (packet) {
		targetId = *reinterpret_cast<const UINT32*>(&packet[offset]);
	}
	if (objectId == targetId) {
		return;
	}
	CCreature *creature = CCreature::GetValidCreatureByObjectId(targetId);
	if (!creature || !creature->hide) {
		return;
	}
	throw IgnorePacket(L"Target in hide");
}

UINT64 __cdecl CUserSocket::OutGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	GUARDED;

	BYTE opcodeRemapped = opcode;

	try {
		if (self->OutGamePacketHandler(packet, opcodeRemapped)) {
			CLog::Debug(CLog::Blue, L"OutGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: 1", opcode, opcodeRemapped);
			return 0x92F0BD;
		}
		CLog::Debug(CLog::Blue, L"OutGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: 0", opcode, opcodeRemapped);
	} catch (const CUserSocket::IgnorePacket &e) {
		CLog::Debug(CLog::Blue, L"OutGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: ignore", opcode, opcodeRemapped);
	}
	return 0x92EF17;
}

UINT64 __cdecl CUserSocket::InGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	GUARDED;

	if (opcode != 0xD0) {
		if (!self->user) {
			CLog::Add(CLog::Red, L"InGamePacketHandlerWrapper: opcode=%d called without user", opcode);
			return 0x92F08A;
		}
		if (!self->user->sd) {
			CLog::Add(CLog::Red, L"InGamePacketHandlerWrapper: opcode=%d called with user without SD", opcode);
			return 0x92F08A;
		}
		switch (opcode) {
		case 0x12: // RequestGameStart again - ignore
			return 0x92EE48;
		case 0x11: // RequestEnterWorld
		case 0xB1: // NetPing
			break;
		default:
			if (!self->user->ext.guard.hasEnteredWorld) {
				CLog::Add(CLog::Red, L"InGamePacketHandlerWrapper: opcode=%d called with user outside the world", opcode);
				return 0x92F08A;
			}
			break;
		}
	}

	if (self->user && self->user->sd && self->user->sd->protectAfterLoginExpiry) {
		switch (opcode) {
		case 0x0F: // MoveBackwardToLocation
		case 0x35: // ChangeMoveType
		case 0x52: // MoveWithDelta
		case 0x75: // MoveToLocationInVehicle
		case 0x01: // Attack
		case 0x1F: // Action
		case 0x56: // RequestActionUse
			self->user->sd->protectAfterLoginExpiry = 0;
			self->SendSystemMessage(3108);
			break;
		}
	}

	BYTE opcodeRemapped = opcode;

	try {
		if (self->InGamePacketHandler(packet, opcodeRemapped)) {
			CLog::Debug(CLog::Blue, L"InGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: 1", opcode, opcodeRemapped);
			return 0x92F08A;
		}
		CLog::Debug(CLog::Blue, L"InGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: 0", opcode, opcodeRemapped);
	} catch (const CUserSocket::IgnorePacket &e) {
		CLog::Debug(CLog::Blue, L"InGamePacketHandlerWrapper: opcode=%d opcodeRemapped=%d: ignore", opcode, opcodeRemapped);
	}
	return 0x92EE48;
}

bool __cdecl CUserSocket::InGamePacketExHandlerWrapper(CUserSocket *self, const BYTE* packet, WORD opcodeEx)
{
	GUARDED;

	if (!self->user) {
		switch (opcodeEx) {
		case 0x01: // RequestManorList
		case 0x3C: // RequestAllCastleInfo
		case 0x3D: // RequestAllFortressInfo
		case 0x3E: // RequestAllAgitInfo
		case 0x36: // called when new character is created
			break;
		default:
			CLog::Add(CLog::Red, L"InGamePacketExHandlerWrapper: opcodeEx=%d called without user", opcodeEx);
			return true;
		}
	}
	if (self->user) {
		if (!self->user->sd) {
			CLog::Add(CLog::Red, L"InGamePacketExHandlerWrapper: opcodeEx=%d called with user without SD", opcodeEx);
			return true;
		}
		switch (opcodeEx) {
		case 0x01: // RequestManorList
		case 0x21: // RequestKeyMapping
		case 0x3C: // RequestAllCastleInfo
		case 0x3D: // RequestAllFortressInfo
		case 0x3E: // RequestAllAgitInfo
		case 0x81:
			break;
		default:
			if (!self->user->ext.guard.hasEnteredWorld) {
				CLog::Add(CLog::Red, L"InGamePacketExHandlerWrapper: opcodeEx=%d called with user outside the world", opcodeEx);
				return true;
			}
			break;
		}
	}

	if (opcodeEx > maxOpcodeEx) {
		CLog::Debug(CLog::Blue, L"InGamePacketExHandlerWrapper: opcodeEx=%d > maxOpcodeEx=%d", opcodeEx, maxOpcodeEx);
		return true;
	}

	WORD opcodeExRemapped = opcodeEx;
	if (Server::GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		switch (opcodeEx) {
		case 0x69: // not implemented
		case 0x6A: // not implemented
		case 0x6B: // not implemented
		case 0x6C: // not implemented
		case 0x6D: // not implemented
		case 0x6E: // not implemented
		case 0x6F: // not implemented
		case 0x70: // not implemented
		case 0x71: // not implemented
		case 0x72: // not implemented
		case 0x73: // not implemented
		case 0x74: // not implemented
		case 0x75: // not implemented
		case 0x76: // not implemented
		case 0x77: // not implemented
		case 0x7C: // not implemented
		case 0x7D: // not implemented
		case 0x7E: // not implemented
		case 0x7F: // not implemented
			CLog::Debug(CLog::Blue, L"InGamePacketExHandlerWrapper: opcodeEx=%d not implemented", opcodeEx);
			return false;
		case 0x78: opcodeExRemapped = 0x65; break;
		case 0x79: opcodeExRemapped = 0x66; break;
		case 0x7A: opcodeExRemapped = 0x67; break;
		case 0x7B: opcodeExRemapped = 0x68; break;
		default: break;
		}
	}

	try {
		bool ret = self->InGamePacketExHandler(packet, static_cast<BYTE>(opcodeExRemapped));
		CLog::Debug(CLog::Blue, L"InGamePacketExHandlerWrapper: opcodeEx=%d opcodeExRemapped=%d: %d",
			opcodeEx, opcodeExRemapped, ret);
		return ret;
	} catch (const CUserSocket::IgnorePacket &e) {
		CLog::Debug(CLog::Blue, L"InGamePacketExHandlerWrapper: opcodeEx=%d opcodeExRemapped=%d: ignore",
			opcodeEx, opcodeExRemapped);
		return true;
	}
}

bool CUserSocket::CallPacketHandler(const BYTE opcode, const BYTE *packet)
{
	GUARDED

	if (Server::GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		if (Server::GetProtocolVersion() == Server::ProtocolVersionGraciaEpilogueUpdate1) {
			if (opcode == 0x1E) {
				return GraciaEpilogue::DiagPacket(this, packet, opcode);
			}
		}
		switch (opcode) {
		case 0x37: return GraciaEpilogue::BuyPacket(this, packet, opcode);
		case 0x40: return GraciaEpilogue::SellPacket(this, packet, opcode);
		default: break;
		}
	}
	PacketHandler handler = packetTable[opcode];
	if (!handler) {
		return false;
	}
	bool ret = handler(this, packet, opcode);
	return ret;
}

bool CUserSocket::CallPacketExHandler(const BYTE opcode, const BYTE *packet)
{ GUARDED

	if (Server::GetProtocolVersion() >= Server::ProtocolVersionGraciaEpilogue) {
		switch (opcode) {
		case 0x0E: return GraciaEpilogue::RequestExEnchantSkillInfo(this, packet, opcode);
		case 0x33: return GraciaEpilogue::RequestExEnchantSkillUntrain(this, packet, opcode);
		case 0x46: return GraciaEpilogue::RequestExEnchantSkillInfoDetail(this, packet, opcode);
		default: break;
		}
	} else {
		switch (opcode) {
		case 0x46: return SkillEnchantFix::RequestExEnchantSkillInfoDetail(this, packet, opcode);
		default: break;
		}
	}
	PacketHandler handler = exHandlers[opcode];
	if (!handler) {
		return false;
	}
	return handler(this, packet, opcode);
}

bool CUserSocket::OutGamePacketHandler(const BYTE *packet, BYTE opcode)
{
	GUARDED;

	const UINT16 &packetLen(*reinterpret_cast<const UINT16*>(packet - 3));
	if (packetLen < 3) {
		return false;
	}

	bool ret = CallPacketHandler(opcode, packet);
	return ret;
}

bool CUserSocket::InGamePacketHandler(const BYTE *packet, BYTE opcode)
{
	GUARDED;

	const UINT16 &packetLen(*reinterpret_cast<const UINT16*>(packet - 3));
	if (packetLen < 3) {
		return false;
	}

	switch (opcode) {
	case 0x19: // UseItem
	case 0x23: // RequestBypassToServer
	case 0x22: // RequestLinkHtml
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (user_->ext.guard.isEnchanting) throw IgnorePacket(L"User is enchanting item");
		if (user_->IsNowTrade()) throw IgnorePacket(L"User is in trade");
		CheckGuard(user_->ext.guard.lastDropItem);
		break;
	}
	case 0x95: // RequestGiveItemToPet
	case 0x17: // RequestDropItem
	case 0x3B: // SendWareHouseDepositList
	case 0xA8: // RequestPackageSend
	case 0x9F: // RequestPrivateStoreSell
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (user_->ext.guard.isEnchanting) throw IgnorePacket(L"User is enchanting item");
		if (user_->IsNowTrade()) throw IgnorePacket(L"User is in trade");
		CheckGuard(user_->ext.guard.lastChangeItem);
		SetGuard(user_->ext.guard.lastDropItem);
		break;
	}
	case 0x5F: // RequestEnchantItem
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (!user_->ext.guard.isEnchanting) throw IgnorePacket(L"User is not enchanting item");
		if (user_->IsNowTrade()) throw IgnorePacket(L"User is in trade");
		CheckGuard(user_->ext.guard.lastDropItem);
		SetGuard(user_->ext.guard.lastChangeItem);
		user_->ext.guard.isEnchanting = false;
		break;
	}
	case 0x56: // RequestActionUse
	case 0x2C: // RequestGetItemFromPet
	case 0x3C: // SendWareHouseWithDrawList
	case 0xA7: // RequestPackageSendableItemList
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (user_->ext.guard.isEnchanting) throw IgnorePacket(L"User is not enchanting item");
		if (user_->IsNowTrade()) throw IgnorePacket(L"User is in trade");
		break;
	}
	case 0x11: // EnterWorld
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (user_->ext.guard.hasEnteredWorld) throw IgnorePacket(L"Already entered world");
		user_->ext.guard.hasEnteredWorld = true;
		break;
	}
	case 0x3A: // Appearing
	case 0x7D: // RequestRestartPoint
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (!user_->ext.guard.hasEnteredWorld) throw IgnorePacket(L"Not entered world");
		break;
	}
	case 0x1B: // AddTradeItem
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (!user_->IsNowTrade()) throw IgnorePacket(L"User not in trade");
		break;
	}
	default:
		break;
	}

	switch (opcode) {
	case 0x1: // Attack
	case 0x1F: // Action
		CheckTargetInHide(packet);
		break;
	case 0x39: // RequestMagicSkillUse
		CheckTargetInHide();
		break;
	case 0x22: // RequestLinkHtml
		return LinkHtmlPacketWrapper(this, packet);
	case 0x23: // RequestBypassToServer
	{
		if (!user) {
			throw IgnorePacket(L"RequestBypassToServer without user");
		}
		if (user->IsNowTrade()) {
			SendSystemMessage(Config::Instance()->server->name.c_str(), L"You can't do this while trading");
			throw IgnorePacket(L"RequestBypassToServer while trading");
		}
		std::string escaped;
		escaped.push_back(0);
		escaped.push_back(0);
		escaped.push_back(opcode);
		bool escapeNeeded = false;
		for (size_t i(0) ; i < packetLen - 3; i += 2) {
			if (packet[i] == '\'' && !packet[i+1]) {
				escaped.push_back('\\');
				escaped.push_back('\x00');
				escapeNeeded = true;
			}
			escaped.push_back(packet[i]);
			escaped.push_back(packet[i+1]);
		}
		if (escapeNeeded) {
			CLog::Add(CLog::Red, L"Had to escape bypass: %s -> %s", packet, escaped.c_str() + 3);
			*reinterpret_cast<UINT16*>(&escaped[0]) = escaped.size() + 3;
			return CallPacketHandler(opcode, reinterpret_cast<const BYTE*>(escaped.c_str() + 3));
		}
		if (Config::Instance()->beta->enabled && std::wstring(reinterpret_cast<const wchar_t*>(packet), 5) == L"beta_") {
			Beta::Bypass(user, std::wstring(reinterpret_cast<const wchar_t*>(packet) + 5));
			return false;
		}
		break;
	}
	case 0x55: // AnswerTradeRequest
	{
		if (!user) {
			throw IgnorePacket(L"AnswerTradeRequest without user");
		}
		int response = *reinterpret_cast<const UINT32*>(packet);
		if (response == 1) {
			SmartPtr<CTrade> trade = CTradeManager::Instance()->GetTrade(user->tradeId);
			if (trade && trade->starterId == user->objectId) {
				throw IgnorePacket(L"AnswerTradeRequest for own request");
			}
		} else if (response) {
			throw IgnorePacket(L"Invalid response %d for AnswerTradeRequest", response);
		}
		break;
	}
	case 0x31: // sell + package sell
	case 0x9A: // buy
	case 0xBB: // dwarven + general manufacture
		{
			CUser *user_ = user;
			if (user_ && !user_->CanOpenPrivateShop(user_->sd->storeMode)) {
				switch (opcode) {
				case 0x31: return CallPacketHandler(0x96, packet);
				case 0x9A: return CallPacketHandler(0x9C, packet);
				case 0xBB: return CallPacketHandler(0xBC, packet);
				default: return false;
				}
			}
		}
	default:
		break;
	}

	return CallPacketHandler(opcode, packet);
}

bool CUserSocket::InGamePacketExHandler(const BYTE *packet, BYTE opcode)
{ GUARDED

	switch (opcode) {
	case 0x41: // RequestRefine
	case 0x42: // RequestConfirmCancelItem
	case 0x32: // ExEnchantSkillSafe
	case 0x0F: // ExEnchantSkill
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		if (user_->ext.guard.isEnchanting) throw IgnorePacket(L"User is enchanting item");
		if (user_->IsNowTrade()) throw IgnorePacket(L"User is in trade");
		CheckGuard(user_->ext.guard.lastDropItem);
		SetGuard(user_->ext.guard.lastChangeItem);
		break;
	}
	case 0x4E: // RequestExCancelEnchantItem
	{
		CUser *user_ = user;
		if (!user_) throw IgnorePacket(L"Packet without user");
		user_->ext.guard.isEnchanting = false;
		break;
	}
	default:
		break;
	}
	return CallPacketExHandler(opcode, packet);
}

void __cdecl CUserSocket::SendSendAbnormalStatusInfoWrapper(CUserSocket *socket, const char *format, BYTE opcode, UINT16 count, UINT32 size, void *data)
{
	if (!Config::Instance()->custom->ipBasedPremiumSystem
		|| !Config::Instance()->custom->ipBasedPremiumSystemShowTime
		|| Config::Instance()->custom->ipBasedPremiumSystemShowTimeSkillId < 0) {

		socket->Send(format, opcode, count, size, data);
	}
	CUser *user = socket->user;
	if (!user) {
		socket->Send(format, opcode, count, size, data);
		return;
	}
	UINT32 premiumEndTime = user->ext.premiumEndTime;
	if (!premiumEndTime) {
		socket->Send(format, opcode, count, size, data);
		return;
	}
	UINT32 now = time(0);
	if (premiumEndTime < now) {
		socket->Send(format, opcode, count, size, data);
		return;
	}
	UINT32 duration = premiumEndTime - now;
	socket->Send("chdhdb", opcode, count + 1,
		Config::Instance()->custom->ipBasedPremiumSystemShowTimeSkillId,
		1, duration, size, data);
}

CompileTimeOffsetCheck(CUserSocket, packetTable, 0x00C0);
CompileTimeOffsetCheck(CUserSocket, user, 0x0528);
CompileTimeOffsetCheck(CUserSocket, ext, 0x0FA0);

