
#include <Common/DataParser.h>
#include <fstream>

bool DataParser::parse(const std::wstring &filename)
{ GUARDED

	std::string filename_;
	for (size_t i(0) ; i < filename.size() ; ++i) {
		filename_.push_back(static_cast<char>(filename[i]));
	}
	std::ifstream ifs(filename_.c_str());
    if (!ifs) {
		CLog::Add(CLog::Red, L"Can't open file '%s' for reading", filename.c_str());
        return false;
    }
	char bom1 = ifs.get();
	char bom2 = ifs.get();
	if (bom1 != 0xFF || bom2 != 0xFE) {
		CLog::Add(CLog::Red, L"Missing/invalid BOM in file '%s'", filename.c_str());
	}
    for (;;) {
        std::wstring line;
		GetLine(ifs, line);
        if (ifs.fail()) {
			if (!ifs.eof()) {
				CLog::Add(CLog::Red, L"Can't read line from '%s'", filename.c_str());
		        return false;
			}
			break;
        }
        if (line.empty()) {
            continue;
        }
        std::map<std::wstring, std::wstring> data;
        std::wstring part;
        std::wstring name;
        bool escape = false;
        for (size_t i(0) ; i < line.size() ; ++i) {
            if (!escape && line[i] == L'\\') {
                escape = true;
                continue;
            } else if (escape) {
                part.push_back(line[i]);
                continue;
            }
            if (line[i] == L'=') {
                name = part;
                part.clear();
            } else if (line[i] == L' ' || line[i] == L'\t') {
                if (!part.empty() && !name.empty()) {
                    data.insert(std::make_pair(name, part));
                }
                name.clear();
                part.clear();
            } else {
                part.push_back(line[i]);
            }
        }
        if (!part.empty() && !name.empty()) {
            data.insert(std::make_pair(name, part));
        }
        OnData(data);
    }
    return true;
}

void DataParser::GetLine(std::ifstream &stream, std::wstring &line)
{
	line.clear();
	for (;;) {
		if (!stream) {
			break;
		}
		wchar_t c = static_cast<wchar_t>(static_cast<unsigned int>(stream.get()) + static_cast<unsigned int>(stream.get()) * 0x100);
		if (c == '\n' || stream.eof()) {
			break;
		} else if (c != '\r') {
			line.push_back(c);
		}
	}
}

