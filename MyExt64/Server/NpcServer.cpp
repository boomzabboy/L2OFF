
#include <Server/NpcServer.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

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

