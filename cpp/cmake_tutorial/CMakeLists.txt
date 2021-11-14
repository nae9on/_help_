# Use at-least 3.0 for Modern CMake
cmake_minimum_required(VERSION 3.16)

set(PRINT_MESSAGES FALSE)

if(${PRINT_MESSAGES})
    message(STATUS "In CMakeLists.txt in cmake_tutorial folder ----------------------")
ENDIF()

# Sets the name of the project and stores it in the PROJECT_NAME variable
project(target_Tutorial VERSION 1.0.0)

# Everything passed to CMake is a string
# quotes are optional but are useful when the string has white spaces as below
# Note: MY_VARIABLE if set here will override an environment variable (if there
# exists one) of the same name
if(${PRINT_MESSAGES})
    set(MY_VARIABLE "The project name is")
    message(STATUS "${MY_VARIABLE} ${PROJECT_NAME}")
    message(STATUS "The project version is ${PROJECT_VERSION}")
endif()

# Copy config.h to the build dir to be later used for pre-processor macro substitution
configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)

# Specify the C++ standard when compiling targets from the current directory and below.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Following flags will be used when compiling targets from the current directory and below.
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GNU GCC")
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "Using Intel C++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Using Visual Studio C++")
    add_compile_options(/W4 /analyze)
endif()

message(STATUS "Using CXX compiler version " ${CMAKE_CXX_COMPILER_VERSION})

# add sub directories (all paths relative to the CMakeLists.txt file)
# every added sub directory should have a CMakeLists.txt file
add_subdirectory(lib)
add_subdirectory(src)

# Compile feature requirements may be specified with the target_compile_features()
# command. For example, if a target must be compiled with compiler support for the
# cxx_constexpr feature: 
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_constexpr)

# In projects that use a large number of commonly available features from a particular
# language standard (e.g. C++ 11) one may specify a meta-feature (e.g. cxx_std_11)
# that requires use of a compiler mode aware of that standard. This is simpler than
# specifying all the features individually, but does not guarantee the existence of
# any particular feature. For example, if C++ 11 features are used extensively in a
# project’s header files, then clients must use a compiler mode aware of C++ 11 or
# above. This can be requested with the code:
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_14)

# List important variables
include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
if(${PRINT_MESSAGES})
    message(STATUS "PrintVariables in cmake_tutorial folder -------------------------")
    print_variables()
    message(STATUS "-----------------------------------------------------------------")
endif()
