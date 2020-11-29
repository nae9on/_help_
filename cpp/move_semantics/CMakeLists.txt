cmake_minimum_required(VERSION 3.16)

project(tutorial_move_semantics)

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0 -fno-elide-constructors)
endif()

FILE(GLOB All ./*.cpp)

add_executable(
"${PROJECT_NAME}"
${All}
)

target_link_libraries("${PROJECT_NAME}")
