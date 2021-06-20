#include <iostream>
#include <regex>

int main()
{
    std::smatch Match;
    
    std::regex Pattern(R"(/research(\d)*/)", std::regex_constants::icase); // case insesitive "research" followed by zero or more digits
    
    std::string CurrentPath{"/a/b/c/research/d/e/f"};
    
    std::string Out;

    // Regex search for the first match
    // Note: if there are more than 1 matches the first match will be used
    if(std::regex_search(CurrentPath, Match, Pattern))
    {
        Out = CurrentPath.substr(0, Match.position()) + std::string(Match[0]) + "x/y";
    }
    else
    {
        std::cout << "Info: research cannot be found in path : " << CurrentPath << std::endl;
    }
    
    std::cout << Out << std::endl;
}
