cmake_minimum_required(VERSION 3.14.6)

# set the project name
project("tutorial" VERSION 1.0.0)

# add compilation flags
if (MSVC)
	add_compile_options(/W4 /analyze)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# add sub directories (all paths relative to the CMakeLists.txt file)
# every added sub directory should have a CMakeLists.txt file which is
# immediately processed by cmake
add_subdirectory(./lib)
add_subdirectory(./src)

# Compile feature requirements may be specified with the target_compile_features() command. For example, if a target must be compiled with compiler support for the cxx_constexpr feature: 
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_constexpr)

# In projects that use a large number of commonly available features from a particular language standard (e.g. C++ 11) one may specify a meta-feature (e.g. cxx_std_11) that requires use of a compiler mode aware of that standard. This is simpler than specifying all the features individually, but does not guarantee the existence of any particular feature. For example, if C++ 11 features are used extensively in a project’s header files, then clients must use a compiler mode aware of C++ 11 or above. This can be requested with the code:
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_14)

# Examples
# "${PROJECT_BINARY_DIR}/../include" 