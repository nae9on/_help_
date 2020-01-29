# add library
add_library(
arithmeticLib SHARED # STATIC or SHARED
./src/arithmetic.cpp
)

# PUBLIC = anyone who is consuming this library also receives it (thus PRIVATE here will prompt error).
# PRIVATE = only this library receives it.
# INTERFACE = anyone who is consuming this library receives it but not the library itself.

# add include directories (all paths relative to the CMakeLists.txt file)
target_include_directories(
arithmeticLib PUBLIC "./include"
)

target_compile_features(arithmeticLib PRIVATE cxx_std_11)
