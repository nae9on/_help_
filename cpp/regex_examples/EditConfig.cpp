#pragma once

#include <regex>
#include <sstream>
#include <string>

class CEditConfigXML
{
public:
    explicit CEditConfigXML(const std::string& Config)
        : m_Config{Config}
    {}

    template<typename T>
    CEditConfigXML& ReplaceText(const std::string& ParameterName, const T& Value)
    {
        std::stringstream From, To;
        From << ParameterName << "=" << "\"(.*?)\""; // "(.*?)" wild card will match 0 or more characters. ? is for lazy match
        To << ParameterName << "=" << "\"" << Value << "\"";
        std::regex Pattern{From.str()};
        m_Config = std::regex_replace(m_Config, Pattern, To.str());
        return *this;
    }

    const std::string& GetConfig() const
    {
        return m_Config;
    }

private:
    std::string m_Config;
};
