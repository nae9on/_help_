message(STATUS "In CMakeLists.txt in lib folder ---------------------------------")

# set the project name
project(arithmeticLib VERSION 2.0.0)

# add library
add_library(
"${PROJECT_NAME}" SHARED # STATIC or SHARED
./src/arithmetic.cpp
)

# PUBLIC = anyone who is consuming this library also receives it.
# PRIVATE = only this library receives it.
# INTERFACE = anyone who is consuming this library receives it but not the library
# itself.

# add include directories (all paths relative to the CMakeLists.txt file)
target_include_directories(
"${PROJECT_NAME}" PUBLIC "./include" # PRIVATE here will prompt error
)

target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_11)

# List important variables
message(STATUS "PrintVariables in lib folder ------------------------------------")
include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
set(flag TRUE)
if(${flag})
	print_variables()
ENDIF()
message(STATUS "-----------------------------------------------------------------")
