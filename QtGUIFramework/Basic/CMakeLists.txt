cmake_minimum_required(VERSION 3.16)

project(project_Basic)

# Make sure Qt is available on your system
set(QT_MIN_VERSION "5.2.1")
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Xml)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC")
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "Using Intel C++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using Visual Studio C++")
    add_compile_options(/W4 /analyze)
endif()

add_executable(
"${PROJECT_NAME}"
main.cpp
)

target_link_libraries("${PROJECT_NAME}" Qt5::Core Qt5::Widgets)
