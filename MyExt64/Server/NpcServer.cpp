
#include <Server/NpcServer.h>
#include <Server/CCreature.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/CSharedCreatureData.h>

void NpcServer::Init()
{
	WriteMemoryBYTES(0x74B579, "\x48\x8B\x94\x24\xA0\x00\x00\x00\x48\x8B\x8C\x24\xB0\x42\x00\x00", 16);
	WriteInstructionCall(0x74B589, reinterpret_cast<UINT32>(SendCreateOnePrivateNearUserWrapper), 0x74B591);
}

NpcServer::NpcServer()
{
}

NpcServer::NpcServer(const NpcServer &other)
{
}

NpcServer::~NpcServer()
{
}

NpcServer* NpcServer::Instance()
{
	return reinterpret_cast<NpcServer*>(0x1634170);
}

void* NpcServer::GetSocket()
{
	return reinterpret_cast<void*(*)(void*)>(0x72CD10)(this);
}

void NpcServer::Send(const char *format, ...)
{
	GUARDED;

	va_list va;
	va_start(va, format);
	SendV(format, va);
	va_end(va);
}

void NpcServer::SendV(const char *format, va_list va)
{
	void *socket = GetSocket();
	if (!socket) {
		CLog::Add(CLog::Red, L"Attempt to write to null socket!");
		return;
	}
	reinterpret_cast<void(*)(void*, const char*, va_list)>(0x859934)(socket, format, va);
}

void __cdecl NpcServer::SendCreateOnePrivateNearUserWrapper(void *self, CCreature *creature, BYTE unused, UINT32 a, UINT32 b, UINT64 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h, UINT32 i, UINT32 j, UINT32 k, wchar_t *l, UINT32 m, UINT32 n, void *o, UINT32 p)
{
	Instance()->Send("cddpddddddddSdbdd", 0x98, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, creature->sd->inZoneId);
}
