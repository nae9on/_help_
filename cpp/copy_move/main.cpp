/*
 * main.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex_vector.h"

ali::complex_vector operator+(const ali::complex_vector& v1, const ali::complex_vector& v2){
	ali::complex_vector temp(v1.n);
	for (size_t i=0; i<v1.n; ++i) temp.data[i] = v1.data[i]+v2.data[i];
	return temp;
}

int main() {

	ali::complex_vector p1;

	ali::complex_vector p2(5);

	ali::complex_vector p3(5, 6);

	ali::complex_vector p4 (p3); // same as ali::complex_vector p4 = p1;

	ali::complex_vector p5;
	p5 = p2;

	std::cout<<"p1"<<" "; p1.print();
	std::cout<<"p2"<<" "; p2.print();
	std::cout<<"p3"<<" "; p3.print();
	std::cout<<"p4"<<" "; p4.print();
	std::cout<<"p5"<<" "; p5.print();

	std::cout<<"-----------------MOVE SEMANTICS-----------------\n";

	ali::complex_vector p6(p4+p3); // why move constructor message not displayed?
	std::cout<<"p6"<<" "; p6.print();

	ali::complex_vector p7;
	p7 = p4+p3; // why move assignment message not displayed?
	std::cout<<"p7"<<" "; p7.print();


	std::cout<<"-----------------END MOVE SEMANTICS-------------\n";

	return 0;
}
