cmake_minimum_required(VERSION 3.16)

project(project_Geometry)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC")
    add_compile_options(-Wall -Wextra -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "Using Intel C++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using Visual Studio C++")
    add_compile_options(/W4 /analyze)
endif()

if (WIN32)
    set(OpenCV_DIR "C:/Users/ahkad/opencv/gnu_build/install")
elseif (UNIX)
    set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
endif()

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(
"${PROJECT_NAME}"
rtree_search.cpp
basic_op.cpp
minimum_bounding_rectangle.cpp
minimum_oriented_bounding_rectangle.cpp
)

target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})
target_link_libraries("${PROJECT_NAME}" ${Boost_LIBRARIES})

message(STATUS "OpenCV_DIR ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")

message(STATUS "Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES ${Boost_LIBRARIES}")
