
#include "CLog.h"

const int CLog::Blue = 1;
const int CLog::Red = 2;

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
	t f = reinterpret_cast<t>(0x6B92AC);
	f(reinterpret_cast<void*>(0x913EDD0), type, format, va);
}

