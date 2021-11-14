if(${PRINT_MESSAGES})
    message(STATUS "In CMakeLists.txt in src folder----------------------------------")
endif()

FILE(GLOB src1allcpp ./src1/*.cpp)
FILE(GLOB src2allcpp ./src2/*.cpp)

add_executable(
"${PROJECT_NAME}"
${src1allcpp}
${src2allcpp}
# ./src2/io.cpp # a file could also be added separately
)

# Specify include directories (all paths relative to the CMakeLists.txt file)
# Place target_include_directories after add_executable
target_include_directories(
"${PROJECT_NAME}" PRIVATE "include" PRIVATE ${PROJECT_BINARY_DIR}
)

FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED)

target_include_directories("${PROJECT_NAME}" PRIVATE ${Boost_INCLUDE_DIRS})

# Link static or shared libraries
# Place target_link_libraries after add_executable and find_package lines, so all
# linked components are known
target_link_libraries("${PROJECT_NAME}" PRIVATE arithmeticLib PRIVATE ${Boost_LIBRARIES})

# List important variables
if(${PRINT_MESSAGES})
    message(STATUS "PrintVariables in src folder-------------------------------------")
    include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
    print_variables()
    message(STATUS "-----------------------------------------------------------------")
endif()
