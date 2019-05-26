/*
 * staticCast.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

// References
// [1] https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019

#include <iostream>

int staticCast()
//int main()
{
	/*
	 * static_cast does no run-time type check, while dynamic_cast does [1]
	 * Therefore, it is left to the programmer to verify that the results of a static_cast
	 * conversion are safe. static_cast should only be in performance-critical code.
	 * Note: The run-time type check done by dynmic_cast is an overhead
	 * Note: dynamic_cast only works on pointers and references
	 */

	char x1 = 'A';
	int y1 = static_cast<int>(x1);
	std::cout<<"Int to char "<<y1<<std::endl;

	float x2 = 3.141;
	double y2 = static_cast<double>(x2);
	std::cout<<"Float to double "<<y2<<std::endl;

	return 0;
}


