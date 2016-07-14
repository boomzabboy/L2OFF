
#include <Common/DataParser.h>
#include <fstream>

bool DataParser::parse(const std::string &filename)
{
	std::ifstream ifs(filename.c_str());
    if (!ifs) {
		CLog::Add(CLog::Red, L"Can't open file '%s' for reading", Widen(filename).c_str());
        return false;
    }
    for (;;) {
        std::string line;
        getline(ifs, line);
        if (ifs.fail()) {
			if (!ifs.eof()) {
				CLog::Add(CLog::Red, L"Can't read line from '%s'", Widen(filename).c_str());
		        return false;
			}
			break;
        }
        if (line.empty()) {
            continue;
        }
        std::map<std::string, std::string> data;
        std::string part;
        std::string name;
        bool escape = false;
        for (size_t i(0) ; i < line.size() ; ++i) {
            if (!escape && line[i] == '\\') {
                escape = true;
                continue;
            } else if (escape) {
                part.push_back(line[i]);
                continue;
            }
            if (line[i] == '=') {
                name = part;
                part.clear();
            } else if (line[i] == ' ' || line[i] == '\t') {
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

