cmake_minimum_required(VERSION 3.16)

project(project_boost_ex)

set(CMAKE_CXX_STANDARD 11)

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

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

FILE(GLOB allcpp ./*.cpp)

add_executable(
"${PROJECT_NAME}"
${allcpp}
)

target_link_libraries("${PROJECT_NAME}" ${Boost_LIBRARIES})

message(STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES ${Boost_LIBRARIES}")
