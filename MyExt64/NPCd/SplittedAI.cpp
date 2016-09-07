
#pragma warning(disable : 996)

#include <NPCd/SplittedAI.h>
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <fstream>
#include <iterator>

unsigned char *SplittedAI::buffer = 0;

void SplittedAI::Init()
{
	WriteInstructionCall(0x5CBA17, reinterpret_cast<UINT32>(ReadSplittedAI));
}

void* SplittedAI::ReadSplittedAI(const wchar_t *filename, UINT32 *filesize)
{
	wchar_t fullPathBuffer[1024];
	GetFullPathNameW(L"..", 1024, fullPathBuffer, 0);
	std::wstring fullPath(L"\\\\?\\");
	fullPath.append(fullPathBuffer);

	CLog::Add(CLog::Blue, L"Loading splitted AI");
	std::ifstream ifs("..\\ai\\classes.txt");
	if (!ifs) {
		CLog::Add(CLog::Red, L"Loading splitted AI: Can't load file classes.txt");
		return 0;
	}
	unsigned int size = 1024 * 1024 * Config::Instance()->npcd->aiBufferSizeMB;
	if (buffer) {
		delete [] buffer;
		buffer = 0;
	}
	buffer = new unsigned char[size];
	unsigned char *end = buffer + size;
	buffer[0] = 0xFF;
	buffer[1] = 0xFE;
	unsigned char *ptr = buffer + 2;
	for (;;) {
		if (ifs.eof()) {
			break;
		}
		std::string line;
		std::getline(ifs, line);
		if (line.empty()) {
			continue;
		}
		for (size_t i = 0 ; i < line.size() ; ++i) {
			if (line[i] == '/') {
				line[i] = '\\';
			}
		}

		std::wstring wline = Widen(line);

		std::pair<unsigned char*, size_t> file = ReadWholeFile((fullPath + L"\\" + wline).c_str());
		if (!file.first) {
			continue;
		}
		for (size_t i = 0 ; i < file.second ; ++i) {
			if (ptr >= end - 1) {
				CLog::Add(CLog::Red, L"Loading splitted AI: Can't fit AI to buffer");
				delete [] file.first;
				delete [] buffer;
				return 0;
			}
			char c = file.first[i];
			if (c > '\x7f') {
				continue;
			}
			*ptr++ = c;
			*ptr++ = 0;
		}
		delete [] file.first;
	}
	*filesize = ptr - buffer;

	std::ofstream ofs("c:\\l2\\test.txt", std::ios::binary);
	ofs.write(reinterpret_cast<const char*>(buffer), *filesize);
	ofs.close();

	return buffer;
}

