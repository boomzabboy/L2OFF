
#include <NPCd/CFString.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

std::map<UINT32, std::wstring> CFString::data;

void CFString::Init()
{
	WriteInstructionCall(0x44941C, reinterpret_cast<UINT32>(GetFormat));
	WriteMemoryBYTES(0x449421, "\x48\x85\xC0\x0F\x84", 5);
	WriteAddress(0x449426, 0x44954A);
	WriteMemoryBYTES(0x44942A, "\x48\x89\xC3\x90\x90\x90", 6);
	WriteMemoryBYTES(0x449481, "\x48\x89\xDA", 3);
	WriteInstructionJmp(0x449484, 0x4494DD);

	NOPMemory(0x475687, 8);
	WriteMemoryBYTES(0x4756A0, "\x48\x89\xDA", 3);
	WriteInstructionCall(0x4756A3, reinterpret_cast<UINT32>(CFString::Add));
	NOPMemory(0x4756A8, 1);
}

const wchar_t* __cdecl CFString::GetFormat(const UINT32 id)
{
	std::map<UINT32, std::wstring>::const_iterator i = data.find(id);
	if (i == data.end()) {
		CLog::Add(CLog::Red, L"[%s][%d] FString doesn't exist. index[%d]", __FILEW__, __LINE__, id);
		return 0;
	}
	return i->second.c_str();
}

void __cdecl CFString::Add(const wchar_t *format, UINT32 id)
{
	std::pair<std::map<UINT32, std::wstring>::const_iterator, bool> i = data.insert(
		std::make_pair(id, std::wstring(format)));

	if (!i.second) {
		CLog::Add(CLog::Red, L"[%s][%d] FString already exists. index[%d]", __FILEW__, __LINE__, id);
	}
}


