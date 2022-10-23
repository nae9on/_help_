cmake_minimum_required(VERSION 3.16)

project(target_clone)

set(CMAKE_CXX_STANDARD 20) # Default value for CXX_STANDARD target property if set when a target is created
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Default value for CXX_STANDARD_REQUIRED target property if set when a target is created
# set(CMAKE_CXX_FLAGS "-std=c++20") # Not a good idea (use -std=c++2a for GCC 9 and earlier)

add_executable(
"${PROJECT_NAME}"
main.cpp
header.h
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
# If the value requested does not result in a compile flag being added for the compiler in use, a previous standard flag will be added instead
# To prevent this decay behavior following can be added
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC " ${CMAKE_CXX_COMPILER_VERSION})
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0.0)
        message(FATAL_ERROR "Required GCC version is at-least 9.0.0")
    endif()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "Using Intel C++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using Visual Studio C++")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /analyze)
endif()
