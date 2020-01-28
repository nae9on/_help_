cmake_minimum_required(VERSION 3.14.6)

# set the project name
project("tutorial" VERSION 1.0.0)

# add compilation flags
if (MSVC)
	add_compile_options(/W4 /analyze)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# add library
add_library(
arithmeticLib SHARED # STATIC or SHARED
arithmetic.cpp
)

# gloab all the .cpp files so that they don't need to be added separately
FILE(GLOB MyCppSources *.cpp)

# add executable
add_executable(
"${PROJECT_NAME}"
main.cpp
complex.cpp 
#${MyCppSources} # to include all .cpp files
)

# Compile feature requirements may be specified with the target_compile_features() command. For example, if a target must be compiled with compiler support for the cxx_constexpr feature: 
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_constexpr)

# In projects that use a large number of commonly available features from a particular language standard (e.g. C++ 11) one may specify a meta-feature (e.g. cxx_std_11) that requires use of a compiler mode aware of that standard. This is simpler than specifying all the features individually, but does not guarantee the existence of any particular feature. For example, if C++ 11 features are used extensively in a project’s header files, then clients must use a compiler mode aware of C++ 11 or above. This can be requested with the code:
target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_11)

# add include directories for libraries
target_include_directories(arithmeticLib PUBLIC
                           "${PROJECT_BINARY_DIR}/../include"
                           )

# add include directories for executable
target_include_directories("${PROJECT_NAME}" PUBLIC
                           "${PROJECT_BINARY_DIR}/../include"
                           )
# link static or shared libraries
target_link_libraries("${PROJECT_NAME}" PUBLIC arithmeticLib)

