/*
 * basic.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: akadar
 */

#include <iostream>

double mysqr(const double x){
	return x*x;
}

constexpr double mysqr2(const double x){
	return x*x;
}

int basic(){
	// Note: static_assert can only be used for constexpr.

	const int x = 10; // x is a constexpr
	static_assert(x==10,"x is 10"); // OK

	const int xsqr = mysqr(x); // xsqr is not a constexpr, it it evaluated at run-time
	//static_assert(xsqr==100,"xsqr is 100"); // Error

	int y = 10;
	const int ysqr = mysqr2(y); // ysqr is not a constexpr, it it evaluated at run-time
	//static_assert(ysqr==100,"ysqr is 100"); // Error

	const int z = 10;
	const int zsqr = mysqr2(z); // zsqr is a constexpr, it it evaluated at compile-time
	static_assert(zsqr==100,"zsqr is 100"); // OK

	std::cout<<"square of x = "<<xsqr<<"\n";
	std::cout<<"square of y = "<<ysqr<<"\n";
	std::cout<<"square of z = "<<zsqr<<"\n";
	return 0;
}


