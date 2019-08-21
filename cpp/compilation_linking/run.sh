#!/bin/bash

#1. Pre-processor expands the pre-processor directives, removes any comments, deals with if, ifdef, ifndef etc.
g++ -E main.cpp > main.pre
g++ -E complex.cpp > complex.pre

#2. Compiler compiles the pre-processed code to generate assembly instructions (human-readable pseudo-code).
g++ -S main.cpp
g++ -S complex.cpp

#3. Assembler will translate the assembly instructions to object code (or byte code).
g++ -c main.cpp
g++ -c complex.cpp

#4. Linker will link all the object files together with other object code for library functions to generate an executable.
g++ -o exec main.o complex.o

