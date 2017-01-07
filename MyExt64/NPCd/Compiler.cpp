
#include <NPCd/Compiler.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <vector>
#include <fstream>

std::string Compiler::filename;
bool Compiler::close = false;

void Compiler::Init()
{
	std::wstring args = GetCommandLineW();
	args.push_back(L' ');
	std::vector<std::wstring> parts;
	std::wstring part;
	for (size_t i = 0 ; i < args.size() ; ++i) {
		if (args[i] == L' ' || args[i] == L'\t') {
			if (!part.empty()) {
				parts.push_back(part);
				part.clear();
			}
		} else {
			part.push_back(args[i]);
		}
	}
	if (parts.size() > 1) {
		for (size_t i = 1 ; i < parts.size() ; ++i) {
			if (parts[i] == L"-c" || parts[i] == L"--close") {
				close = true;
			} else if (filename.empty()) {
				filename = Narrow(parts[i]);
			} else {
				wchar_t buffer[4096];
				if (parts[0].size() < 2048) {
					wsprintf(buffer, L"Usage:\r\n%s [-c|--close] [FILENAME]", parts[0].c_str());
				} else {
					wsprintf(buffer, L"Usage:\r\n%s... [-c|--close] [FILENAME]", parts[0].substr(0, 2048).c_str());
				}
				MessageBox(0, buffer, L"Invalid arguments", 0);
				exit(0);
			}
		}
	}
	if (filename.empty()) {
		return;
	}
	WriteInstructionCall(0x55A890+0x185, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x55A890+0x6A2, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BB4D0+0x495, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BB4D0+0x505, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BB4D0+0x685, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BC0C0+0x1C, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BE07C+0x162, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BE07C+0x18C, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5BE234+0x6D, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x818, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x92F, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0xBD2, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1552, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1AF5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1BA5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1C2D, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1CB8, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x1EA3, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x20E0, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2306, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2408, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x260A, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x283A, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x28B6, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x29A5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2A2A, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2B7F, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2C6A, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2D22, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x2FF6, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x30A5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3276, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x335E, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3446, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3520, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x38E1, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x39CB, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3C9F, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3DF3, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x3EF5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x403D, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x40E2, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4340, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x43E5, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4542, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4627, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x46D2, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x497C, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x49DB, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4A69, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4BA2, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4EA1, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x4F37, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x5017, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x50CA, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x5366, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x53C4, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x5531, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x5C3AC8+0x558F, reinterpret_cast<UINT32>(LogError));
	WriteInstructionCall(0x54817C, reinterpret_cast<UINT32>(Compile));
	WriteInstructionJmp(0x42B140, reinterpret_cast<UINT32>(exit));
	WriteMemoryBYTES(0x665D40, L"Global\\CONSOLE_LOG_NASC", 50);
	WriteInstructionJmp(0x475826, 0x475846);
}

int Compiler::LogError(void*, const wchar_t* format, ...)
{
	va_list va;
    va_start(va, format);
	CLog::AddV(CLog::Red, format, va);
    va_end(va);
	return 1;
}

void Compiler::Compile()
{
	std::string outputFilename = filename + ".obj";

	size_t pos = filename.rfind(".");
	if (pos != std::string::npos) {
		outputFilename = filename.substr(0, pos) + ".obj";
	}

	std::wstring wfilename = Widen(filename);
	std::wstring woutputFilename = Widen(outputFilename);

	for (size_t i = 0 ; i < 10 ; ++i) {
		CLog::Add(CLog::Blue, L" ");
	}
	CLog::Add(CLog::Blue, L"Going to compile %s to %s", wfilename.c_str(), woutputFilename.c_str());
	CLog::Add(CLog::Blue, L" ");

	if (!std::wifstream(filename.c_str())) {
		CLog::Add(CLog::Red, L"Can't open input file %s", wfilename.c_str());
		Done(false);
	}

	*reinterpret_cast<int*>(0x37886B8) = 1; // enable logging

	Parser parser;
	reinterpret_cast<void*(*)(void*)>(0x5C9980)(&parser); // construct parser

	reinterpret_cast<void(*)(UINT64, UINT64, FILE*)>(0x55A890)(0x36E58D0, 0x649CA8, 0); // load pch db

	// this is how we can add @variables
	// reinterpret_cast<void(*)(UINT64, const wchar_t*, int)>(0x55B18C)(0x36E58D0, L"variable", 123);

	InputFile inputFile;
	reinterpret_cast<void(*)(InputFile*, const char*, int, int)>(0x4086F8)(&inputFile, filename.c_str(), 1, 1); // open input file

	if (inputFile.something2[inputFile.something1] & 6) { // check input file OK
		CLog::Add(CLog::Red, L"Can't open input file!");
		Done(false);
	}

	if (!reinterpret_cast<bool(*)(Parser*, const wchar_t*)>(0x5BE2B4)(&parser, wfilename.c_str())) { // give file to parser
		CLog::Add(CLog::Red, L"Failed to create parser");
		Done(false);
	}

	reinterpret_cast<void(*)(const char*)>(0x419D84)(outputFilename.c_str()); // open output

	reinterpret_cast<void(*)(int, int, int, int, int, int)>(0x419E40)( // write header
		sizeof(void*), 69, 79, 2, 2, 0);

	*reinterpret_cast<UINT32*>(reinterpret_cast<char*>(&parser) + 0x110) = 4; // mode?

	bool error = reinterpret_cast<UINT32(*)(Parser*)>(0x5D7F70)(&parser); // compile
	int errors = *reinterpret_cast<UINT32*>(0x37886C0); // get error count

	reinterpret_cast<void(*)()>(0x419F00)(); // close output file

	if (error || errors) {
		CLog::Add(CLog::Red, L"Compilation failed, error count = %d", errors);
	} else {
		CLog::Add(CLog::Blue, L"Compilation done");
	}

	Done(true);
}

void Compiler::Done(bool status)
{
	if (close && status) {
		exit(0);
	}
	for (;;) {
		Sleep(100);
	}
}

