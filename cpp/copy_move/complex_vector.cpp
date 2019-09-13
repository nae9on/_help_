/*
 * complex_vector.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 */

#include <iostream>
#include "complex_vector.h"

namespace ali {

// constructor with 0 argument
complex_vector::complex_vector() {
	n = 0;
	data = nullptr;
	std::cout<<"My default constructor which overrides the default\n";
}

// constructor with 1 argument
complex_vector::complex_vector(size_t n_) {
	n = n_;
	data = new int[n];
	for (size_t i=0; i<n; i++) {
		data[i] = 0.0;
	}
	std::cout<<"My ordinary constructor with size argument\n";
}

// constructor with 2 arguments
complex_vector::complex_vector(size_t n_, int c_) {
	n = n_;
	data = new int[n];
	for (size_t i=0; i<n; i++) {
		data[i] = c_;
	}
	std::cout<<"My ordinary constructor with size and data argument\n";
}

// copy constructor
complex_vector::complex_vector(const complex_vector& v) : n{v.n}, data{new int[v.n]} {
	for (size_t i=0; i<n; i++) {
		data[i] = v.data[i];
	}
	std::cout<<"My copy constructor which overrides the default\n";
}

// copy assignment
complex_vector& complex_vector::operator=(const complex_vector& v) {
	if (this!=&v) {
		delete[] data; // deletes the content of data
		n = v.n; // overwrites n
        // allocate a new block of memory and assign it to data
		data = new int[n];
		for (size_t i=0; i<n; i++) {
			data[i] = v.data[i];
		}
		std::cout<<"My copy assignment which overrides the default\n";
	}
	return *this;
}

// move constructor
complex_vector::complex_vector(complex_vector&& v) : data{v.data}, n{v.n}{
	// Following prevents the destructor from freeing resources (such as memory) multiple times.
	v.data = nullptr;
	v.n = 0;
	std::cout<<"My move constructor which overrides the default\n";
}

// move assignment
complex_vector& complex_vector::operator=(complex_vector&& v) {
	if (this!=&v){
		delete[] data;
		data = v.data;
		n = v.n;
		v.data = nullptr;
		v.n = 0;
		std::cout<<"My move assignment which overrides the default\n";
	}
	return *this;
}

complex_vector::~complex_vector() {
	if(data!=nullptr){
		delete[] data;
		std::cout << "In destructor, deleting resource\n";
	}
}

void complex_vector::print() {
	std::cout<<"Size "<<n<<", ";
	for (size_t i=0; i<n; i++)
		std::cout<<data[i]<<" ";
	std::cout<<"\n";
}

}
