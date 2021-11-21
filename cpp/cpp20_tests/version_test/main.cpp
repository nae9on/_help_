// g++ -std=c++20 main.cpp

#include <iostream>

int main()
{
#if __cplusplus >= 202002L
    // C++20 (and later) code
    std::cout << "C++20 (or later): version " << __cplusplus << std::endl;
#else
    std::cout << "Not yet C++20: version " << __cplusplus <<  std::endl;
#endif
    return 0;
}
