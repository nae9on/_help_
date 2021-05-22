cmake_minimum_required(VERSION 3.16)

project(project_compilation_linking)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
	add_compile_options(/W4 /analyze)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

set (CMAKE_CXX_STANDARD 11)

FILE(GLOB allcpp ./*.cpp)
FILE(GLOB allheaders ./*.h)

add_executable(
"${PROJECT_NAME}"
${allcpp}
${allheaders}
)

target_link_libraries("${PROJECT_NAME}")
