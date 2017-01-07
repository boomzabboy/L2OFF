
#pragma once

#include <windows.h>
#include <string>

class Compiler {
public:
	class Parser {
	public:
		//unsigned char padding[0x1B0];
		unsigned char padding[0x1000];
	};

	class InputFile {
	public:
		/* 0x0000 */ unsigned char padding0x0000[0x0004-0x0000];
		/* 0x0004 */ UINT32 something1;
		/* 0x0008 */ unsigned char padding0x0008[0x0010-0x0008];
		/* 0x0010 */ char something2[0xF0];
	};

	static void Init();
	static int LogError(void*, const wchar_t* format, ...);
	static void Compile();
	static void Done(bool status);

	static std::wstring exeFilename;
	static std::string filename;
	static bool close;
};

