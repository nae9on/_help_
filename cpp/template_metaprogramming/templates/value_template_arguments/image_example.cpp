#include <iostream>

enum class EImageDataType
{
    ByteImage,
    ShortImage,
    IntImage,
    FloatImage
};

template<EImageDataType T> struct ImageTraits;

template<>
struct ImageTraits<EImageDataType::ByteImage>
{
    typedef std::uint8_t ValueType;
    enum { NumBytesPerElement = sizeof(ValueType) };
};

template<>
struct ImageTraits<EImageDataType::ShortImage>
{
    typedef std::uint16_t ValueType;
    enum { NumBytesPerElement = sizeof(ValueType) };
};

template<>
struct ImageTraits<EImageDataType::IntImage>
{
    typedef int ValueType;
    enum { NumBytesPerElement = sizeof(ValueType) };
};

template<>
struct ImageTraits<EImageDataType::FloatImage>
{
    typedef float ValueType;
    enum { NumBytesPerElement = sizeof(ValueType) };
};

template<EImageDataType ImageDataType = EImageDataType::ByteImage,
         typename T = typename ImageTraits<ImageDataType>::ValueType>
EImageDataType Test()
{
    return ImageDataType;
}

int main()
{
    std::cout << static_cast<int>(Test()) << std::endl;
    std::cout << static_cast<int>(Test<EImageDataType::ByteImage>()) << std::endl;
    std::cout << static_cast<int>(Test<EImageDataType::ShortImage>()) << std::endl;
    std::cout << static_cast<int>(Test<EImageDataType::IntImage>()) << std::endl;
    std::cout << static_cast<int>(Test<EImageDataType::FloatImage>()) << std::endl;
    return 0;
}
