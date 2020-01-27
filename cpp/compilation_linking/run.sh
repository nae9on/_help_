#!/bin/bash

#1. Pre-processor
g++ -E main.cpp > main.pre
g++ -E complex.cpp > complex.pre
g++ -E arithmetic.cpp > arithmetic.pre

#2. Compiler
g++ -S main.cpp
g++ -S complex.cpp
g++ -S arithmetic.cpp
# It creates main.s, complex.s, arithmetic.s

#3. Assemble
g++ -c main.cpp
g++ -c complex.cpp
g++ -c -fpic arithmetic.cpp
# It creates main.o, complex.o and arithmetic.o

mkdir -p lib

#4. Create a static library
ar rvs ./lib/arithmeticStatic.a arithmetic.o # option1
ar rvs ./lib/libarithmeticStaticCopy.a arithmetic.o # option2

#5. Create a shared library
g++ -o ./lib/arithmeticShared.so -shared arithmetic.o # option 1
g++ -o ./lib/libarithmeticSharedCopy.so -shared arithmetic.o # option 2

#6. Linker

# Static linking
g++ -o exec1 main.o complex.o ./lib/arithmeticStatic.a # option 1
g++ -o exec1Copy main.o complex.o -L./lib -larithmeticStaticCopy # option 1

# Dynamic linking
g++ -o exec2 main.o complex.o ./lib/arithmeticShared.so # option 2
g++ -o exec2Copy main.o complex.o -L./lib -larithmeticSharedCopy # option 2

# List shared libraries
echo "Shared libraries exec2 depends on are: "
ldd exec2
echo "Shared libraries exec2Copy depends on are: "
ldd exec2Copy
