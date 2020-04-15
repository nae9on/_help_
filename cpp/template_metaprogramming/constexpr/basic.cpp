/*
 * basic.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: akadar
 *
 * Reference: https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=vs-2019
 */

#include <iostream>
#include <cmath>

double mysqr(double x){
	return x*x;
}

// constexpr indicates that the value, or return value, is constant and, where possible,
// is computed at compile time.
constexpr double mysqr2(double x){
	return x*x;
}

// A function marked constexpr, is evaluated at run time (like a regular function)
// 1. When it is called with non-constexpr arguments, or
// 2. When its value isn't required at compile time
constexpr double sqroot(double x){
	using std::sqrt;
	return sqrt(x);
}

int basic(){

	const int x = 10; // Is x a constexpr? Not necessarily!

	// Syntax constexpr literal-type identifier = constant-expression;
	constexpr int xx = 10; // OK, xx is a constexpr

	const double xsqr = mysqr(xx);
	//constexpr double xxsqr = xsqr;  // Error, xsqr is not a constant-expression.

	int y = 10;
	//constexpr double ysqr = mysqr2(y); // Error, mysqr2(y) is not a constant-expression.

	constexpr int z = 10;
	constexpr double zsqr = mysqr2(z); // OK, mysqr2(z) is a constant-expression.

	constexpr double pi =  3.14;
	const double piroot1 = sqroot(pi); // evaluated at run-time
	constexpr double piroot2 = sqroot(pi); // evaluated at compile-time
	//constexpr double root = piroot1; // Error, piroot1 is not a constant-expression
	constexpr double root = piroot2; // OK, piroot2 is a constant-expression

	std::cout<<"End of main\n";

	(void) x;
	(void) xsqr;
	(void) y;
	(void) zsqr;
	(void) piroot1;
	(void) root;
	return 0;
}
