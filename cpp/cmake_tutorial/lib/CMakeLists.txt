if(${PRINT_MESSAGES})
    message(STATUS "In CMakeLists.txt in lib folder ---------------------------------")
endif()

project(arithmeticLib VERSION 2.0.0)

add_library(
"${PROJECT_NAME}" SHARED # STATIC or SHARED
./src/arithmetic.cpp
)

target_include_directories(
# PRIVATE here will prompt error because the header is included in src
"${PROJECT_NAME}" PUBLIC "include"
)

# List important variables
if(${PRINT_MESSAGES})
    message(STATUS "PrintVariables in lib folder ------------------------------------")
    include(${CMAKE_SOURCE_DIR}/PrintVariables.cmake)
    print_variables()
    message(STATUS "-----------------------------------------------------------------")
endif()

