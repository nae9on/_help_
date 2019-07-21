/*
 * conversion_operator.cpp
 *
 *  Created on: Jul 21, 2019
 *      Author: akadar
 */

#include <iostream>

class math_pi{
public:

	// Defining a conversion operator.
	// It allows conversion from a custom type (math_pi in this case) to another type (int, double etc)
	// without having to call a special member function explicitly.
	operator double();

	explicit operator int();
};

math_pi::operator double(){
	std::cout<<"conversion to double\n";
	return 3.14;
}

math_pi::operator int(){
	std::cout<<"conversion to int\n";
	return 3;
}

int main(){

	math_pi pi;

	// implicit conversion from math_pi to double is allowed
	double x = pi;
	std::cout<<"pi (upto 2 decimal digits) = "<<x<<"\n";

	// implicit conversion from math_pi to int is not allowed
	int y = pi;
	std::cout<<"pi (without decimal digits) = "<<y<<"\n";

	// implicit conversion from math_pi to int is not allowed (since scientific pi is not an int :))
	int z = (int)pi;
	std::cout<<"pi (without decimal digits) = "<<z<<"\n";

	return 0;
}
