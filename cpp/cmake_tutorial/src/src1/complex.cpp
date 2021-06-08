/*
 * complex.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex.h"
#include "arithmetic.h"
#include "io.h"

cx::cx(my_double r, my_double i){
    real = r;
    imag = i;
}

void cx::print_abs(){
    fancyIO(std::cout)<<getAbs(real,imag)<<"\n";
}
