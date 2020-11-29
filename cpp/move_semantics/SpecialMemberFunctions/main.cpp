/*
 * main.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://channel9.msdn.com/Series/C9-Lectures-Stephan-T-Lavavej-Standard-Template-Library-STL-
 * [2] https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2019
 * [3] https://stackoverflow.com/questions/50834215/is-there-a-way-to-disable-copy-elision-in-c-compiler
 */

#include <iostream>
#include "complex_vector.h"

using namespace cvector;

complex_vector operator+(const complex_vector& v1, const complex_vector& v2){
	std::cout<<"In + operator\n";
	complex_vector temp(v1.n);
	for (size_t i=0; i<v1.n; ++i) temp.data[i] = v1.data[i]+v2.data[i];
	std::cout<<"Summed up in temporary\n";
	return temp;
}

complex_vector square(const complex_vector& v1){
	std::cout<<"In square\n";
	complex_vector temp(v1.n);
	for (size_t i=0; i<v1.n; ++i) temp.data[i] = v1.data[i]*v1.data[i];
	std::cout<<"Squared in temporary\n";
	return temp;
}

int main() {

	complex_vector p1(5);

	complex_vector p2(5);

	complex_vector p3(5, 6);

	complex_vector p4(p3); // same as complex_vector p4 = p1;

	complex_vector p5(5);
	p5 = p2;

	std::cout<<"p1"<<" "; p1.print();
	std::cout<<"p2"<<" "; p2.print();
	std::cout<<"p3"<<" "; p3.print();
	std::cout<<"p4"<<" "; p4.print();
	std::cout<<"p5"<<" "; p5.print();

	std::cout<<"-----------------MOVE CONSTRUCTOR-----------------\n";

	// Note: move constructor may not be called due to copy elision.
	// Use flag -fno-elide-constructors to disable copy elision [3].
	// make sure c++11 compilation flag is used.

	// To see the difference disable move semantics and use c++98 flag!

	complex_vector p6(complex_vector(6));
	p6.print();

	std::cout<<"--------------------------------------------------\n";

	complex_vector p7(p3+p4); // Why move constructor called twice?
	p7.print();

	std::cout<<"-----------------MOVE ASSIGNMENT------ -----------\n";

	complex_vector p8;
	p8 = complex_vector(8,5);
	p8.print();

	std::cout<<"--------------------------------------------------\n";

	complex_vector p8sq(8,5);
	p8sq = square(p8sq); // Why move constructor called here?
	p8sq.print();

	std::cout<<"-----------------END MOVE SEMANTICS------- -------\n";

	return 0;
}
