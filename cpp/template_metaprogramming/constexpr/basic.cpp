/*
 * basic.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: akadar
 *
 * Reference:
 * https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=vs-2019
 * https://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const
 *
 * constexpr (=constant expression) is a keyword which when applied to
 * 1. objects mean constness + compile time evaluation
 * 2. functions mean, their return value may be used in a constant expression (depending on
 * whether the function arguments are constexpr or not)
 */

#include <iostream>
#include <cmath>

// not a constexpr => return value cannot be used in a constant expression
double mysqr(double x){
	return x*x;
}

// a constexpr => return value may be be used in a constant expression
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

	const int x{10}; // Is x a constexpr? Yes even without the keyword constexpr!

	// Syntax constexpr literal-type identifier = constant-expression;
	constexpr int xx = x;

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
