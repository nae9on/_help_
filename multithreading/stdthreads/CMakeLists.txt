cmake_minimum_required(VERSION 3.16)

project(project_stdthreads)

if (MSVC)
        add_compile_options(/W4 /analyze)
else()
        add_compile_options(-Wall -Wextra -Wpedantic -O0)
endif()

add_executable(
"${PROJECT_NAME}"
producer_consumer_using_condition_variables.cpp
)

target_link_libraries("${PROJECT_NAME}")
