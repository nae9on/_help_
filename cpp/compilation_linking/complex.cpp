/*
 * complex.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex.h"

//void funcX(){}; // error
//class X{}; X cx; // error
//int x; // error

void funcY();
class Y;
extern int global_y;
const double global_pi{3.1415}; // OK const qualified variables have internal linkage
static int xx = 1;

#define abs(r,i) (std::sqrt(r*r+i*i))

ComplexNumber::ComplexNumber(my_double r, my_double i){
	real = r;
	imag = i;
}

void ComplexNumber::print_abs(){
	std::cout<<"\nIn complex.cpp y = "<<global_y<<"\n";
	std::cout << "Absolute value = "<<abs(real,imag)<<"\n";
}
