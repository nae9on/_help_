/*
 * basic.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: akadar
 *
 * Reference: https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=vs-2019 *
 */

#include <iostream>
#include <cmath>

double mysqr(double x){
	return x*x;
}

// Unlike const, constexpr can also be applied to functions and class constructors.
constexpr double mysqr2(double x){
	return x*x;
}

constexpr double sqroot(double x){
	using std::sqrt;
	return sqrt(x);
}

int basic(){

	const int x = 10;
	constexpr int xx = x; // OK, indicates x is a constant-expression.

	const int xsqr = mysqr(x);
	//constexpr int xxsqr = xsqr;  // Error, indicates xsqr is not a constant-expression.

	int y = 10;
	//constexpr int ysqr = mysqr2(y); // Error, indicates mysqr2(y) is not a constant-expression.

	const int z = 10;
	constexpr int zsqr = mysqr2(z); // OK, mysqr2(z) is a constant-expression.

	const int introot = sqroot(4.4);
	//const double introot = sqroot(4.4); // introot is not constexpr, why?
	constexpr double root = introot;

	std::cout<<"End of main\n";

	(void) xx;
	(void) xsqr;
	(void) y;
	(void) zsqr;
	(void) root;
	return 0;
}
