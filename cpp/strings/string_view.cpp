#include <iostream>
#include <string>
#include <string_view>

std::string_view GetExtension(std::string_view Path)
{
    auto last_period_idx = Path.find_last_of(".");
    if(last_period_idx == std::string::npos) { last_period_idx = 0; }
    return {&Path[last_period_idx], Path.size()-last_period_idx}; // file has no extension
}

int main()
{
  std::cout << GetExtension("dir\\dir\\dir\\") << "\n";
  std::cout << GetExtension("dir\\dir\\dir\\file.ext") << "\n";
}
