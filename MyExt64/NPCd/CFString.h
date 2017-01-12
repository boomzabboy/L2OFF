
#pragma once

#include <windows.h>
#include <map>
#include <string>

class CFString {
public:
	static void Init();
	static const wchar_t* __cdecl GetFormat(const UINT32 id);
	static void __cdecl Add(const wchar_t *format, UINT32 id);

	static std::map<UINT32, std::wstring> CFString::data;
};

