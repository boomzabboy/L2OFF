
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/Config.h>

const int CLog::Blue = 1;
const int CLog::Red = 2;
const int CLog::CallStack = 0x10000;

CLog* CLog::instance = 0;
UINT32 CLog::logfn = 0;
UINT32 CLog::stackfn = 0;

void CLog::Add(const int type, const wchar_t *format, ...)
{
	va_list va;
	va_start(va, format);
	AddV(type, format, va);
	va_end(va);
}

void CLog::AddV(const int type, const wchar_t *format, va_list va)
{
	typedef void (__thiscall *t)(void*, const int, const wchar_t*, va_list);
	t f = reinterpret_cast<t>(logfn);
	f(reinterpret_cast<void*>(instance), type & 0xFFFF, format, va);
	if (type & 0x10000) {
		LogCallStack(type & 0xFFFF);
	}
}

void CLog::Debug(const int type, const wchar_t *format, ...)
{
	if (!Config::Instance()->server->debug) {
		return;
	}
	va_list va;
	va_start(va, format);
	DebugV(type, format, va);
	va_end(va);
}

void CLog::DebugV(const int type, const wchar_t *format, va_list va)
{
	if (!Config::Instance()->server->debug) {
		return;
	}
	typedef void (__thiscall *t)(void*, const int, const wchar_t*, va_list);
	t f = reinterpret_cast<t>(logfn);
	f(reinterpret_cast<void*>(instance), type & 0xFFFF, format, va);
	if (type & 0x10000) {
		LogCallStack(type & 0xFFFF);
	}
}

void CLog::LogCallStack(const int type)
{
	reinterpret_cast<void(*)(int)>(stackfn)(type);
}

