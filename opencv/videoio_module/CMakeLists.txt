cmake_minimum_required(VERSION 3.16)

project(VideoIO)

# this overrides the OpenCV_DIR env variable (if set previously)
set(OpenCV_DIR "C:/Users/ahkad/opencv/gnu_build/install")

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(tutorial main.cpp)

target_link_libraries(tutorial ${OpenCV_LIBS})

message(STATUS "OpenCV_DIR ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
message(STATUS "OpenCV_LIB_PATH  ${OpenCV_LIB_PATH}")
