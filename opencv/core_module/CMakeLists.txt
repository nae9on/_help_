cmake_minimum_required(VERSION 3.16)

project(project_core_module)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# this overrides the OpenCV_DIR env variable (if set previously)
# set(OpenCV_DIR "C:/Users/ahkad/opencv/gnu_build/install")

if (MSVC)
	add_compile_options(/W4 /analyze)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -O3)
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
