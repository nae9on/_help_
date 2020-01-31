message(STATUS "In CMakeLists.txt in src folder----------------------------------")

# Use glob module to find all the pathnames matching a specified pattern.
# All the .cpp files are found so that they don't need to be added separately.
FILE(GLOB src1allcpp ./src1/*.cpp)
FILE(GLOB src2allcpp ./src2/*.cpp)

# Add the target executable
add_executable(
"${PROJECT_NAME}"
${src1allcpp}
${src2allcpp}
# ./src2/io.cpp # a file could also be added separately
)

# Specify include directories (all paths relative to the CMakeLists.txt file)
# Place target_include_directories after add_executable
target_include_directories(
"${PROJECT_NAME}" PRIVATE "./include"
)

# Include path for boost
# find_package is used to search for available boost libraries. It defers searching
# for Boost to FindBoost.cmake, which is default installed with CMake. Upon finding
# Boost, the find_package() call will have filled many variables (check the reference
# for FindBoost.cmake). Among these are BOOST_INCLUDE_DIRS, Boost_LIBRARIES and 
# Boost_XXX_LIBRARY variabels, with XXX replaced with specific Boost libraries. 
# You can use these to specify include_directories and target_link_libraries.
FIND_PACKAGE(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

# Link static or shared libraries
# Place target_link_libraries after add_executable and find_package lines, so all
# linked components are known
target_link_libraries("${PROJECT_NAME}" PRIVATE arithmeticLib ${Boost_LIBRARIES})

# List important variables
message(STATUS "PrintVariables in src folder-------------------------------------")
include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
set(flag TRUE)
if(${flag})
	print_variables()
ENDIF()
message(STATUS "-----------------------------------------------------------------")
