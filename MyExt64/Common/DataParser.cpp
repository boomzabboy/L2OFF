
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
	bool bomOk = false;
	unsigned char bom1 = ifs.peek();
	if (bom1 == 0xff) {
		ifs.get();
		unsigned char bom2 = ifs.peek();
		if (bom2 == 0xfe) {
			ifs.get();
			bomOk = true;
		}
	}
	if (!bomOk) {
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
		if (!stream.good()) {
			break;
		}
		unsigned char c1 = stream.get();
		unsigned char c2 = stream.get();
		wchar_t c = static_cast<wchar_t>(
			static_cast<unsigned int>(c1) + static_cast<unsigned int>(c2) * 0x100);
		if (c == L'\n' || stream.eof()) {
			break;
		} else if (c != L'\r') {
			line.push_back(c);
		}
	}
}

