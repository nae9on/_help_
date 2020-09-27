cmake_minimum_required(VERSION 3.16)

project(tutorial_xml_parser)

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0)
endif()

add_executable(
"${PROJECT_NAME}"
main.cpp
tinystr.h
tinyxml.h
tinyxml.cpp
tinystr.cpp
tinyxmlerror.cpp
tinyxmlparser.cpp
)

target_link_libraries("${PROJECT_NAME}")
