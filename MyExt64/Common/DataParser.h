
#pragma once

#include <Common/CLog.h>
#include <Common/Utils.h>
#include <map>
#include <sstream>

class DataParser {
public:
    bool parse(const std::string &filename);
    virtual void OnData(const std::map<std::string, std::string> &data) = 0;

    template<class T>
    T Convert(const std::string &value, const T &defaultValue = T())
    {
        T ret;
        std::stringstream ss;
        ss << value;
        ss >> ret;
        if (!ss) {
			CLog::Add(CLog::Red, L"Invalid lexical cast for '%s'", Widen(value).c_str());
            return defaultValue;
        }
        return ret;
    }

    template<class T>
    T Get(const std::map<std::string, std::string> &data, const std::string &name)
    {
        std::map<std::string, std::string>::const_iterator idata(data.find(name));
        if (idata == data.end()) {
			CLog::Add(CLog::Red, L"Missing '%s'", Widen(name).c_str());
            return T();
        }
        return Convert<T>(idata->second);
    }

    template<class T>
    T Get(const std::map<std::string, std::string> &data, const std::string &name, const T &defaultValue)
    {
        std::map<std::string, std::string>::const_iterator idata(data.find(name));
        if (idata == data.end()) {
            return defaultValue;
        }
        return Convert<T>(idata->second);
    }

    bool Exists(const std::map<std::string, std::string> &data, const std::string &name)
    {
        return data.find(name) != data.end();
    }
};

