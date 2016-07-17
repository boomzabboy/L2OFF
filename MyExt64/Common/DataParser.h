
#pragma once

#include <Common/CLog.h>
#include <Common/Utils.h>
#include <map>
#include <sstream>

class DataParser {
public:
    bool parse(const std::wstring &filename);
    virtual void OnData(const std::map<std::wstring, std::wstring> &data) = 0;

    template<class T>
    T Convert(const std::wstring &value, const T &defaultValue = T())
    {
        T ret;
        std::wstringstream ss;
        ss << value;
        ss >> ret;
        if (!ss) {
			CLog::Add(CLog::Red, L"Invalid lexical cast for '%s'", value.c_str());
            return defaultValue;
        }
        return ret;
    }

    template<class T>
    T Get(const std::map<std::wstring, std::wstring> &data, const std::wstring &name)
    {
        std::map<std::wstring, std::wstring>::const_iterator idata(data.find(name));
        if (idata == data.end()) {
			CLog::Add(CLog::Red, L"Missing '%s'", name.c_str());
            return T();
        }
        return Convert<T>(idata->second);
    }

    template<class T>
    T Get(const std::map<std::wstring, std::wstring> &data, const std::wstring &name, const T &defaultValue)
    {
        std::map<std::wstring, std::wstring>::const_iterator idata(data.find(name));
        if (idata == data.end()) {
            return defaultValue;
        }
        return Convert<T>(idata->second);
    }

    bool Exists(const std::map<std::wstring, std::wstring> &data, const std::wstring &name)
    {
        return data.find(name) != data.end();
    }

protected:
	void GetLine(std::ifstream &stream, std::wstring &line);
};

