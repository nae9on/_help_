#pragma once

#include <iostream>
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

int main()
{
    std::string Config = R"(
                         <Image Width="1920" Height="1080" Format="JPEG" Type="Fast" IsColored="1">
                            <Data Data="Dummy image" />
                         </Image>
                         )";

    std::string EditedConfig = CEditConfigXML(Config).ReplaceText("Format", "PNG").ReplaceText("IsColored", "0").GetConfig();

    std::cout << EditedConfig << std::endl;

    return 0;
}
