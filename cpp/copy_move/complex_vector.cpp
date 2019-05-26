/*
 * complex_vector.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex_vector.h"

namespace ali {

complex_vector::complex_vector() {
	n = 0;
	data = nullptr;
	std::cout<<"My constructor\n";
}

complex_vector::complex_vector(size_t n_) {
	n = n_;
	data = new complex[n];
	for (size_t i=0; i<n; i++) {
		data[i].real = 0.0;
		data[i].imag = 0.0;
	}
	std::cout<<"Ordinary constructor with size argument\n";
}

complex_vector::complex_vector(size_t n_, complex c_) {
	n = n_;
	data = new complex[n];
	for (size_t i=0; i<n; i++) {
		data[i].real = c_.real;
		data[i].imag = c_.imag;
	}
	std::cout<<"Ordinary constructor with size and data argument\n";
}

void complex_vector::print() {
	std::cout<<"Size "<<n<<std::endl ;
	for (size_t i=0; i<n; i++)
		std::cout<<"data["<<i<<"] = "<<data[i].real<<"+"<<data[i].imag<<"i"<<std::endl ;
	std::cout<<"\n\n";
}


complex_vector::complex_vector(const complex_vector& v) : n{v.n}, data{new complex[n]} {
	for (size_t i=0; i<n; i++) {
		data[i].real = v.data[i].real;
		data[i].imag = v.data[i].imag;
	}
	std::cout<<"My copy constructor which overrides the default\n";
}

complex_vector& complex_vector::operator=(const complex_vector& v) {
	n = v.n; // overwrites n
	complex* p = new complex[n];
	for (size_t i=0; i<n; i++) {
		p[i].real = v.data[i].real;
		p[i].imag = v.data[i].imag;
	}
	delete[] data; // deletes the content of data
	data = p;
	std::cout<<"My copy assignment which overrides the default\n";
	return *this;

}

complex_vector::~complex_vector() {
	delete[] data;
	std::cout<<"Destructor\n";
}
}
