
#pragma once

#include <windows.h>
#include <stdarg.h>

class CLog {
public:
	static const int Red;
	static const int Blue;

	static const int CallStack;

	static void Add(const int type, const wchar_t* format, ...);
	static void AddV(const int type, const wchar_t *format, va_list va);
	static void LogCallStack(const int type);

	static CLog *instance;
	static UINT32 logfn;
	static UINT32 stackfn;
};

