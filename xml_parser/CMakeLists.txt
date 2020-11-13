cmake_minimum_required(VERSION 3.16)

project(tutorial_xml_parser)

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0)
endif()

FILE(GLOB TinyXmlcpp ./TinyXml/*.cpp)

add_executable(
"${PROJECT_NAME}"
main.cpp
${TinyXmlcpp}
)

target_link_libraries("${PROJECT_NAME}")
