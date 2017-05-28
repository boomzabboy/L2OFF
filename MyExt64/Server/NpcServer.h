
#pragma once

#include <stdarg.h>
#include <windows.h>

class NpcServer {
private:
	NpcServer();
	NpcServer(const NpcServer &other);
	~NpcServer();

public:
	static void Init();
	static NpcServer* Instance();
	void* GetSocket();
	void Send(const char *format, ...);
	void SendV(const char *format, va_list va);
	static void __cdecl SendCreateOnePrivateNearUserWrapper(void *self, class CCreature *creature, BYTE unused, UINT32 a, UINT32 b, UINT64 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h, UINT32 i, UINT32 j, UINT32 k, wchar_t *l, UINT32 m, UINT32 n, void *o, UINT32 p);
	static bool NpcEx(void *socket, const unsigned char *bytes);
	static bool NpcWhisper(void *socket, const unsigned char *bytes);
	static bool NpcSetAbilityItemDrop(void *socket, const unsigned char *bytes);
	static bool NpcShowBuySell(void *socket, const unsigned char *bytes);
};

