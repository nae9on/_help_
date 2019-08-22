/*
 * main.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 *
 * References:
 * [1] http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/compile.html
 * [2] https://www.calleerlandsson.com/the-four-stages-of-compiling-a-c-program/
 * [3] https://en.cppreference.com/w/cpp/preprocessor/conditional
 * [4] http://www.cplusplus.com/forum/articles/10627/
 * [5] https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=vs-2019
 *
 * C++ program compilation is a 4-step procedure [1,2]:
 * Pre-processing -> compilation -> assembly -> linking
 * 1. Pre-processor expands the pre-processor directives (statements preceding with #).
 * g++ -E main.cpp > main.pre
 * g++ -E complex.cpp > complex.pre
 *
 * 2. Compiler compiles the expanded code to generate assembly instructions (human-readable pseudo-code).
 * g++ -S main.cpp
 * g++ -S complex.cpp
 *
 * 3. Assembler will translate the assembly instructions to object code (or byte code).
 * g++ -c main.cpp
 * g++ -c complex.cpp
 *
 * 4. Linker will link all the object files together with other object code for library functions to generate an executable.
 * g++ -o exec main.o complex.o
 *
 * Note: When you compile a program, each .cpp file is compiled independently into a compilation unit.
 * The compiler has no knowledge of what names are declared in other compilation units. [5]
 */

#include <iostream>
#include "complex.h" //  Why header files ? Refer [4]

// Example conditional compilation [3]
#define FLAG 0

int main(){

#ifndef FLAG
	std::cout<<"Flag is not defined\n" // Error is not visible to the compiler
#elif FLAG==1
	std::cout<<"Flag is 1\n" // Error is not visible to the compiler
#else
	std::cout<<"FLAG is defined and is not 1\n";
#endif

	cx c;
	c.print_abs();
	return 0;
}
