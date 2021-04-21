#include <iostream>

enum EColorFormat
{
    YUV,
    RGB
};

// This can be in the header
template<EColorFormat ColorFormat>
void GetColor();

// The following can be in .cpp
template<>
void GetColor<EColorFormat::YUV>()
{
    std::cout << "YUV" << std::endl;
}

template<>
void GetColor<EColorFormat::RGB>()
{
    std::cout << "RGB" << std::endl;
}

int main()
{
    GetColor<EColorFormat::YUV>();
    GetColor<EColorFormat::RGB>();
    return 0;
}

