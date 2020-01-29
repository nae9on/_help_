# add library
add_library(
arithmeticLib SHARED # STATIC or SHARED
./src/arithmetic.cpp
)

# add include directories (all paths relative to the CMakeLists.txt file)
target_include_directories(
arithmeticLib PUBLIC "./include"
)

target_compile_features(arithmeticLib PUBLIC cxx_std_11)
