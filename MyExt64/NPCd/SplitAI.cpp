
#pragma warning(disable : 996)

#include <NPCd/SplitAI.h>
#include <Common/CLog.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <fstream>
#include <iterator>
#include <sstream>

unsigned char *SplitAI::buffer = 0;

void SplitAI::Init()
{
	WriteInstructionCall(0x5CBA17, reinterpret_cast<UINT32>(ReadSplitAI));
}

void* SplitAI::ReadSplitAI(const wchar_t *filename, UINT32 *filesize)
{
	wchar_t fullPathBuffer[1024];
	GetFullPathNameW(L"..", 1024, fullPathBuffer, 0);
	std::wstring fullPath(L"\\\\?\\");
	fullPath.append(fullPathBuffer);

	CLog::Add(CLog::Blue, L"Loading Split AI");
	std::ifstream ifs("..\\ai\\classes.txt");
	if (!ifs) {
		CLog::Add(CLog::Red, L"Loading Split AI: Can't load file classes.txt");
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

	IdMapping idMapping;

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
			CLog::Add(CLog::Red, L"Loading Split AI: Can't load file %s", wline.c_str());
			continue;
		}

		idMapping.Prepare();

		line.clear();
		for (size_t i = 0 ; i < file.second ; ++i) {
			char c = file.first[i];
			if (static_cast<unsigned char>(c) < 0x80 && c != '\r' && c != '\n') {
				line.push_back(c);
			}
			if (c == '\n' || i == file.second - 1) {
				line = idMapping.ProcessLine(line);
				line.push_back('\r');
				line.push_back('\n');
				if (line.size() * 2 > end - ptr) {
					CLog::Add(CLog::Red, L"Loading Split AI: Can't fit AI to buffer, increase size in config");
					delete [] file.first;
					delete [] buffer;
					return 0;
				}
				for (size_t j = 0 ; j < line.size() ; ++j) {
					*ptr++ = line[j];
					*ptr++ = 0;
				}
				line.clear();
			}
		}
		delete [] file.first;
	}
	*filesize = ptr - buffer;

	if (Config::Instance()->npcd->dumpSplitAI) {
		std::ofstream ofs("..\\dump\\ai.obj", std::ios::binary);
		ofs.write(reinterpret_cast<const char*>(buffer), *filesize);
		ofs.close();
	}

	return buffer;
}

SplitAI::IdMapping::IdMapping() :
	header(true),
    lastLabelId(1),
	lastStringId(1)
{
}

std::string SplitAI::IdMapping::ProcessLine(const std::string &line)
{
	if (line.empty()) {
		return line;
	}

	std::vector<std::string> tokens = Tokenize(line);
	if (tokens.empty()) {
		return "";
	}

	if (header) {
		if (tokens[0] == "class") {
			header = false;
		} else {
			return line;
		}
	}

	if (!tokens[0].find("L")) {
		long id = GetLabel(tokens[0]);
		std::stringstream ss;
		ss << "L" << id;
		return ss.str();
	} else if (!tokens[0].find("S") && tokens[0][tokens[0].size() - 1] == '.') {
		long id = GetString(tokens[0].substr(0, tokens[0].size() - 1));
		std::stringstream ss;
		ss << "S" << id << ".";
		for (size_t i = 1 ; i < tokens.size() ; ++i) {
			ss << " " << tokens[i];
		}
		return ss.str();
	} else if (tokens[0] == "jump" || tokens[0] == "branch_true" || tokens[0] == "branch_false") {
		if (tokens.size() < 2) {
			CLog::Add(CLog::Red, L"Missing instruction %s operand: %s", Widen(tokens[0]).c_str(), Widen(line).c_str());
			return line;
		}
		long id = GetLabel(tokens[1]);
		std::stringstream ss;
		ss << "\t" << tokens[0] << " L" << id;
		return ss.str();
	} else if (tokens[0] == "push_string") {
		if (tokens.size() < 2) {
			CLog::Add(CLog::Red, L"Missing instruction %s operand: %s", Widen(tokens[0]).c_str(), Widen(line).c_str());
			return line;
		}
		long id = GetString(tokens[1]);
		std::stringstream ss;
		ss << "\t" << tokens[0] << " S" << id;
		return ss.str();
	}

	return line;
}

void SplitAI::IdMapping::Prepare()
{
	labels.clear();
	strings.clear();
}

long SplitAI::IdMapping::GetLabel(const std::string &oldId)
{
	std::pair<std::map<std::string, long>::iterator, bool> res = labels.insert(
		std::pair<std::string, long>(oldId, lastLabelId));
	if (res.second) {
		++lastLabelId;
	}
	return res.first->second;
}

long SplitAI::IdMapping::GetString(const std::string &oldId)
{
	std::pair<std::map<std::string, long>::iterator, bool> res = strings.insert(
		std::pair<std::string, long>(oldId, lastStringId));
	if (res.second) {
		++lastStringId;
	}
	return res.first->second;
}

