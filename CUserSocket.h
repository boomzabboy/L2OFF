
#pragma once

#include "Utils.h"
#include <windows.h>
#include <stdexcept>

class CUserSocket {
public:
	typedef bool (__cdecl *PacketHandler)(CUserSocket*, const BYTE*, BYTE);
	static void Init();

	class IgnorePacket : public std::exception {
	public:
		IgnorePacket(const wchar_t *format, ...);
	};

	class Ext {
	friend class CUserSocket;
	private:
		Ext();
		~Ext();
	};

	static CUserSocket* __cdecl Constructor(CUserSocket *self, SOCKET s);
	static CUserSocket* __cdecl Destructor(CUserSocket *self, bool isMemoryFreeUsed);

	static UINT64 __cdecl OutGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static UINT64 __cdecl InGamePacketHandlerWrapper(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static bool __cdecl InGamePacketExHandlerWrapper(CUserSocket *self, const BYTE* packet, WORD opcodeEx);

	bool CallPacketHandler(const BYTE opcode, const BYTE *packet);
	bool CallPacketExHandler(const BYTE opcode, const BYTE *packet);

	bool OutGamePacketHandler(const BYTE *packet, BYTE opcode);
	bool InGamePacketHandler(const BYTE *packet, BYTE opcode);
	bool InGamePacketExHandler(const BYTE *packet, BYTE opcode);

	class CUser* GetUser();
	void Send(const char *format, ...);
	void SendV(const char *format, va_list va);
	void SendSystemMessage(UINT32 id);
	void SendSystemMessage(const wchar_t *sender, const wchar_t *message);

	/* 0x0000 */ unsigned char padding0x0000[0xC0];
	/* 0x00C0 */ PacketHandler *packetTable;
	/* 0x00C8 */ unsigned char padding0x00C8[0x460];
	/* 0x0528 */ class CUser *user;
	/* 0x0530 */ unsigned char padding0x0530[0xA70];
	/* EXT DATA BEGIN AT 0x0FA0 */
	/* 0x0FA0 */ Ext ext;

	static PacketHandler *exHandlers;
};

