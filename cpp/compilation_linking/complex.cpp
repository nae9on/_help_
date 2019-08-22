/*
 * complex.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex.h"

#define abs(r,i) (std::sqrt(r*r+i*i))

cx::cx(my_double r, my_double i){
	real = r;
	imag = i;
}

void cx::print_abs(){
	std::cout << "Absolute value is "<<abs(real,imag)<<"\n";
}
