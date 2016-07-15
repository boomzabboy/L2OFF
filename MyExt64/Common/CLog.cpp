
#include <Common/CLog.h>
#include <Common/Utils.h>

const int CLog::Blue = 1;
const int CLog::Red = 2;

CLog* CLog::instance = 0;
UINT32 CLog::logfn = 0;

void CLog::Add(const int type, const wchar_t *format, ...)
{ GUARDED

	va_list va;
	va_start(va, format);
	AddV(type, format, va);
	va_end(va);
}

void CLog::AddV(const int type, const wchar_t *format, va_list va)
{ GUARDED

	typedef void (__thiscall *t)(void*, const int, const wchar_t*, va_list);
	t f = reinterpret_cast<t>(logfn);
	f(reinterpret_cast<void*>(instance), type, format, va);
}

