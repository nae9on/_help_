cmake_minimum_required(VERSION 3.16)

project(project_stdthreads)

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0)
endif()

add_executable(
"${PROJECT_NAME}"
improved_producer_consumer.cpp
)

target_link_libraries("${PROJECT_NAME}")
