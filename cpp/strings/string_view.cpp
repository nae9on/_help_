#include <iostream>
#include <string>
#include <string_view>

std::string_view GetBeforeExtension(std::string_view Path)
{
    auto Dot_location = Path.find_last_of(".");

    if(Dot_location == std::string::npos)
    {
        return Path; // return path when dot not found
    }

    return {&Path[0], Dot_location};
}

std::string_view GetExtension(std::string_view Path)
{
    auto Dot_location = Path.find_last_of(".");

    if(Dot_location == std::string::npos)
    {
        return std::string{}; // return empty string when dot not found
    }

    return {&Path[Dot_location], Path.size()-Dot_location};
}

int main()
{
  std::cout << GetExtension("dir\\dir\\dir\\") << "\n";
  std::cout << GetExtension("dir\\dir\\dir\\file.ext") << "\n";
}
