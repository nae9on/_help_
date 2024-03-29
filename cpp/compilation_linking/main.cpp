/*
 * main.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 *
 * References:
 * [0] The C++ Programming Language - Bjarne Stroustrup Chapter 15
 * [1] http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/compile.html
 * [2] https://www.calleerlandsson.com/the-four-stages-of-compiling-a-c-program/
 * [3] https://en.cppreference.com/w/cpp/preprocessor/conditional
 * [4] http://www.cplusplus.com/forum/articles/10627/
 * [5] https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=vs-2019
 */

#include <iostream>
#include "complex.h" //  Why header files ? Refer [4]
// In fact header files are old concept, C++20 will have Modules

#include "arithmetic.h"

// Example conditional compilation [3]
#define FLAG 0

//void funcX(){}; // error
//class X{}; X obj; // error
//int x; // error

void funcY(); // OK does not violate ODR when the same function is declared in different TU's
class Y; // OK when declaring a type
int global_y{7}; // OK when extern is used in other compilation units
double global_pi{3.14};  // OK const qualified variables have internal linkage
static int xx = 1; // OK static variables have internal linkage

int main(){

#ifndef FLAG
	std::cout<<"Flag is not defined" // Error is not visible to the compiler
#elif FLAG==1
	std::cout<<"Flag is 1" // Error is not visible to the compiler
#else
	std::cout<<"FLAG is defined and is not 1";
#endif

	ComplexNumber c;
	c.print_abs();
	std::cout<<"In main.cpp y = "<<global_y<<"\n";
	std::cout<<"Absolute value = "<<getAbs(c.getReal(),c.getImag())<<"\n";
	return 0;
}
