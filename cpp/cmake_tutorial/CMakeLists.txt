cmake_minimum_required(VERSION 3.16)

set(PRINT_MESSAGES FALSE)

if(${PRINT_MESSAGES})
    message(STATUS "In CMakeLists.txt in cmake_tutorial folder ----------------------")
endif()

project(target_Tutorial VERSION 1.0.0)

if(${PRINT_MESSAGES})
    set(MY_VARIABLE "The project name is")
    message(STATUS "${MY_VARIABLE} ${PROJECT_NAME}")
    message(STATUS "The project version is ${PROJECT_VERSION}")
endif()

# Copy config.h to the build dir to be later used for pre-processor macro substitution
configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Following flags will be used when compiling targets from the current directory and below
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /analyze)
endif()

# add sub directories (all paths relative to the CMakeLists.txt file)
# every added sub directory should have a CMakeLists.txt file
add_subdirectory(lib)
add_subdirectory(src)

# List important variables
if(${PRINT_MESSAGES})
    include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
    message(STATUS "PrintVariables in cmake_tutorial folder -------------------------")
    print_variables()
    message(STATUS "-----------------------------------------------------------------")
endif()
