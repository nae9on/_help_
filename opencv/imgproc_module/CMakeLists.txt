cmake_minimum_required(VERSION 3.16)

project(project_imgproc_module)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

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

FILE(GLOB allcpp ./*.cpp)

add_executable(
"${PROJECT_NAME}"
${allcpp}
)

target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})

message(STATUS "OpenCV_DIR ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
