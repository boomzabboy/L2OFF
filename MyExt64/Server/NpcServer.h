
#pragma once

#include <stdarg.h>

class NpcServer {
private:
	NpcServer();
	NpcServer(const NpcServer &other);
	~NpcServer();

public:
	static NpcServer* Instance();
	void* GetSocket();
	void Send(const char *format, ...);
	void SendV(const char *format, va_list va);
};

