
#pragma once

#include <windows.h>
#include "Utils.h"

typedef int (__cdecl *CUserSocketAssemble_t)(char*, int, const char*, ...);
typedef const unsigned char* (__cdecl *CUserSocketDisassemble_t)(const unsigned char*, const char*, ...);

class CUserSocket {
public:
	static void HookPacketHandlers();

protected:
	static bool __cdecl DummyPacketEx(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static bool __cdecl RequestExSkillEnchantInfoDetailGraciaEpilogue(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static int __cdecl AssembleInventoryUpdateItem1GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q);
	static int __cdecl AssembleInventoryUpdateItem2GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssembleSkillListItemGraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT8 d);
	static int __cdecl AssembleItemListItem1GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT32 d, UINT64 e, UINT16 f, UINT16 g, UINT16 h, UINT32 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT32 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT32 w);
	static int __cdecl AssembleItemListItem2GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT16 a, UINT16 b, UINT32 c, UINT32 d, UINT32 e, UINT64 f, UINT16 g, UINT16 h, UINT16 i, UINT32 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT32 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT16 w, UINT32 x);
	static CUserSocketAssemble_t Assemble;
	static CUserSocketDisassemble_t Disassemble;

public:
	class CUser* GetUser();
	void Send(const char *format, ...);
	void SendV(const char *format, va_list va);

	/* 0x0000 */ unsigned char padding0x0000[0xc0];
	/* 0x00C0 */ UINT64* packetTable;
	/* 0x00C8 */ unsigned char padding0x00c8[0x460];
	/* 0x0528 */ class CUser *user;
};

CompileTimeOffsetCheck(CUserSocket, packetTable, 0x00C0);
CompileTimeOffsetCheck(CUserSocket, user, 0x0528);

