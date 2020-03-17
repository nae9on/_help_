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
extern int y;
const double pi{3.1415};

#define abs(r,i) (std::sqrt(r*r+i*i))

cx::cx(my_double r, my_double i){
	real = r;
	imag = i;
}

void cx::print_abs(){
	std::cout<<"\ny="<<y<<"\n";
	std::cout << "Absolute value is "<<abs(real,imag)<<"\n";
}
