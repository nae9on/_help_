/*
 * staticCast.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

// References
// [1] https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019

#include <iostream>

int main_static()
{
	/*
	 * static_cast does no run-time type check [1].
	 * Therefore, it is left to the programmer to verify that the results of a static_cast
	 * conversion are safe. static_cast should only be used in performance-critical code
	 * and when the desired conversion is inherently low-level
	 */

	// When converting from an int to char, the programmer is responsible for the loss of bits.
	int x = 7081989;
	char ch = static_cast<int>(x);
	std::cout<<"Int to char "<<ch<<std::endl;

	// This is OK.
	float x2 = 3.141;
	double y2 = static_cast<double>(x2);
	std::cout<<"Float to double "<<y2<<std::endl;

	return 0;
}


