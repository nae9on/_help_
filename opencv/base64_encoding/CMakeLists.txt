cmake_minimum_required(VERSION 3.16)

project(project_base64_encoding)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC")
    add_compile_options(-Wall -Wextra -Wpedantic -O0)
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

FILE(GLOB allh ./*.h)
FILE(GLOB allcpp ./*.cpp)
FILE(GLOB TinyXmlcpp ./TinyXml/*.cpp)

add_executable(
"${PROJECT_NAME}"
${allh}
${allcpp}
${TinyXmlcpp}
)

target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})

message(STATUS "OpenCV_DIR ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
