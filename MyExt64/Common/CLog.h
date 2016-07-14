
#pragma once

#include <windows.h>
#include <stdarg.h>

class CLog {
public:
	static const int Red;
	static const int Blue;

	static void Add(const int type, const wchar_t* format, ...);
	static void CLog::AddV(const int type, const wchar_t* format, va_list va);

	static CLog *instance;
};

