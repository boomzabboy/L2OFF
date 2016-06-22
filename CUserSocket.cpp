
#include "CUserSocket.h"
#include "CUser.h"
#include "CLog.h"
#include "Utils.h"
#include "MyExt64.h"
#include "GraciaEpilogue.h"
#include <new>

CUserSocket::PacketHandler *CUserSocket::exHandlers = reinterpret_cast<CUserSocket::PacketHandler*>(0x121C0D60);

static WORD maxOpcodeEx = 0x68;

CUserSocket::IgnorePacket::IgnorePacket(const wchar_t *format, ...)
: std::exception()
{
	if (MyExt64::IsDebug()) {
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

	switch (MyExt64::GetProtocolVersion()) {
	case MyExt64::ProtocolVersionGraciaFinal:
	case MyExt64::ProtocolVersionGraciaFinalUpdate1:
		maxOpcodeEx = 0x68;
		break;
	case MyExt64::ProtocolVersionGraciaEpilogue:
		maxOpcodeEx = 0x7D;
		break;
	case MyExt64::ProtocolVersionGraciaEpilogueUpdate1:
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

	if (MyExt64::GetProtocolVersion() == MyExt64::ProtocolVersionGraciaFinalUpdate1) {
		ReplaceOutExOpcode(0x7ED0D8, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED213, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED3DB, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED537, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDA07, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDF2F, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x47613C, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x476383, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x915BE1, 0xA9); // FE:A8 -> FE:A9
		ReplaceOutExOpcode(0x596FD1, 0xAA); // FE:A9 -> FE:AA
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
	if (MyExt64::GetProtocolVersion() >= MyExt64::ProtocolVersionGraciaEpilogue) {
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
		ReplaceOutExOpcode(0x596FD1, 0xBB); // FE:A9 -> FE:BB
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
		ReplaceOutExOpcode(0x8CFBC3, 0xBE); // FE:AB -> FE:BE
		ReplaceOutExOpcode(0x8ADEB8, 0xBE); // FE:AC -> FE:BD
	}

	WriteMemoryBYTES(0x912880, "\x30\xC0", 2); // ONLY FOR TESTING - DummyPacket not to disconnect user
}

CUserSocket* __cdecl CUserSocket::Constructor(CUserSocket *self, SOCKET s)
{
	typedef CUserSocket* (__cdecl *t)(CUserSocket*, SOCKET);
	t f = reinterpret_cast<t>(0x93CADC);
	CUserSocket *ret = f(self, s);
	new (&ret->ext) Ext();
	return ret;
}

CUserSocket* __cdecl CUserSocket::Destructor(CUserSocket *self, bool isMemoryFreeUsed)
{
	typedef CUserSocket* (__cdecl *t)(CUserSocket*, bool);
	t f = (t)0x0092DE7C;
	self->ext.~Ext();
	return f(self, isMemoryFreeUsed);
}

CUserSocket::Ext::Ext()
{
}

CUserSocket::Ext::~Ext()
{
}

CUser* CUserSocket::GetUser()
{
	return user;
}

void CUserSocket::Send(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	SendV(format, va);
	va_end(va);
}

void CUserSocket::SendV(const char *format, va_list va)
{
	typedef void (__thiscall *t)(CUserSocket*, const char*, va_list);
	t f = reinterpret_cast<t>(0x859934);
	f(this, format, va);
}

UINT64 __cdecl CUserSocket::OutGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	BYTE opcodeRemapped = opcode;

	try {
		return self->OutGamePacketHandler(packet, opcodeRemapped) ? 0x92F0BD : 0x92EF17;
	} catch (const CUserSocket::IgnorePacket &e) {
		return 0x92EE0C;
	}
}

UINT64 __cdecl CUserSocket::InGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	BYTE opcodeRemapped = opcode;

	try {
		return self->InGamePacketHandler(packet, opcodeRemapped) ? 0x92F08A : 0x92EE48;
	} catch (const CUserSocket::IgnorePacket &e) {
		return 0x92EE0C;
	}
}

bool __cdecl CUserSocket::InGamePacketExHandlerWrapper(CUserSocket *self, const BYTE* packet, WORD opcodeEx)
{
	if (opcodeEx > maxOpcodeEx) {
		return true;
	}

	WORD opcodeExRemapped = opcodeEx;
	if (MyExt64::GetProtocolVersion() >= MyExt64::ProtocolVersionGraciaEpilogue) {
		switch (opcodeEx) {
		case 0x69: return false; // not implemented
		case 0x6A: return false; // not implemented
		case 0x6B: return false; // not implemented
		case 0x6C: return false; // not implemented
		case 0x6D: return false; // not implemented
		case 0x6E: return false; // not implemented
		case 0x6F: return false; // not implemented
		case 0x70: return false; // not implemented
		case 0x71: return false; // not implemented
		case 0x72: return false; // not implemented
		case 0x73: return false; // not implemented
		case 0x74: return false; // not implemented
		case 0x75: return false; // not implemented
		case 0x76: return false; // not implemented
		case 0x77: return false; // not implemented
		case 0x78: opcodeExRemapped = 0x65; break;
		case 0x79: opcodeExRemapped = 0x66; break;
		case 0x7A: opcodeExRemapped = 0x67; break;
		case 0x7B: opcodeExRemapped = 0x68; break;
		case 0x7C: return false; // not implemented
		case 0x7D: return false; // not implemented
		case 0x7E: return false; // not implemented
		case 0x7F: return false; // not implemented
		default: break;
		}
	}

	try {
		//CLog::Add(CLog::Blue, L"InGamePacketExHandlerWrapper: call InGamePacketExHandler(packet, %02X)", opcodeExRemapped);
		bool ret = self->InGamePacketExHandler(packet, static_cast<BYTE>(opcodeExRemapped));
		//CLog::Add(CLog::Blue, L"InGamePacketExHandlerWrapper: InGamePacketExHandler(packet, %02X) returned %d", opcodeExRemapped, ret ? 1 : 0);
		return ret;
	} catch (const CUserSocket::IgnorePacket &e) {
		//CLog::Add(CLog::Blue, L"InGamePacketExHandlerWrapper: InGamePacketExHandler(packet, %02X) raise IgnorePacket", opcodeExRemapped);
		return true;
	}
}

bool CUserSocket::CallPacketHandler(const BYTE opcode, const BYTE *packet)
{
	if (MyExt64::GetProtocolVersion() >= MyExt64::ProtocolVersionGraciaEpilogue) {
		switch (opcode) {
		case 0x37: return GraciaEpilogue::BuyPacket(this, packet, opcode);
		case 0x40: return GraciaEpilogue::SellPacket(this, packet, opcode);
		default: break;
		}
	}
	PacketHandler handler = packetTable[opcode];
	if (!handler) {
		//CLog::Add(CLog::Blue, L"CallPacketHandler %d: no handler", opcode);
		return false;
	}
	bool ret = handler(this, packet, opcode);
	//CLog::Add(CLog::Blue, L"CallPacketHandler %d %p: %d", opcode, handler, ret ? 1 : 0);
	return ret;
}

bool CUserSocket::CallPacketExHandler(const BYTE opcode, const BYTE *packet)
{
	//CLog::Add(CLog::Blue, L"CallPacketHandlerEx %02X", opcode);
	if (MyExt64::GetProtocolVersion() >= MyExt64::ProtocolVersionGraciaEpilogue) {
		switch (opcode) {
		case 0x0E: return GraciaEpilogue::RequestExEnchantSkillInfo(this, packet, opcode);
		case 0x33: return GraciaEpilogue::RequestExEnchantSkillUntrain(this, packet, opcode);
		case 0x46: return GraciaEpilogue::RequestExEnchantSkillInfoDetail(this, packet, opcode);
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
	bool ret = CallPacketHandler(opcode, packet);
	//CLog::Add(CLog::Blue, L"OutGamePacketHandler: %02X -> %d", opcode, ret ? 1 : 0);
	return ret;
}

bool CUserSocket::InGamePacketHandler(const BYTE *packet, BYTE opcode)
{
	bool ret = CallPacketHandler(opcode, packet);
	//CLog::Add(CLog::Blue, L"InGamePacketHandler: %02X -> %d", opcode, ret ? 1 : 0);
	return ret;
}

bool CUserSocket::InGamePacketExHandler(const BYTE *packet, BYTE opcode)
{
	bool ret = CallPacketExHandler(opcode, packet);
	//CLog::Add(CLog::Blue, L"InGamePacketExHandler: %02X -> %d", opcode, ret ? 1 : 0);
	return ret;
}

CompileTimeOffsetCheck(CUserSocket, packetTable, 0x00C0);
CompileTimeOffsetCheck(CUserSocket, user, 0x0528);
CompileTimeOffsetCheck(CUserSocket, ext, 0x0FA0);

