/*
 * main.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex_vector.h"

int main() {

	ali::complex_vector p0;
	std::cout<<std::endl;

	ali::complex_vector p1(5);
	std::cout<<std::endl;

	ali::complex_vector p2(5, ali::complex {1,2});
	std::cout<<std::endl;

	ali::complex_vector p3(5, ali::complex {3,4});
	std::cout<<std::endl;

	ali::complex_vector p4 (p1); // same as ali::complex_vector p4 = p1;
	std::cout<<std::endl;

	ali::complex_vector p5;
	p5 = p4;
	std::cout<<std::endl;

	ali::complex_vector p6;

	std::cout<<"\n\n";
	std::cout<<"p0"<<std::endl; p0.print();
	std::cout<<"p1"<<std::endl; p1.print();
	std::cout<<"p2"<<std::endl; p2.print();
	std::cout<<"p3"<<std::endl; p3.print();
	std::cout<<"p4"<<std::endl; p4.print();
	std::cout<<"p5"<<std::endl; p5.print();
	std::cout<<"p6"<<std::endl; p6.print();
	//p1 = std::move(p2);

	return 0;
}
