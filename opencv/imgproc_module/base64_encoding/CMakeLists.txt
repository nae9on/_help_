cmake_minimum_required(VERSION 3.16)

project(tutorial_base64encoding)

# this overrides the OpenCV_DIR env variable (if set previously)
# set(OpenCV_DIR "C:/Users/ahkad/opencv/gnu_build/install")

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0)
endif()

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
"${PROJECT_NAME}"
main.cpp
base64.h
base64.cpp
)

target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})

message(STATUS "OpenCV_DIR ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS ${OpenCV_LIBS}")
message(STATUS "OpenCV_LIB_PATH  ${OpenCV_LIB_PATH}")
