/*
 * explicit_constructor.cpp
 *
 *  Created on: Jul 21, 2019
 *      Author: akadar
 */

#include <iostream>

class myVector1{
public:
	myVector1(size_t n_): n{n_}, data{new double[n_]{}} {std::cout<<"myVector1 constructor called\n";}
	void print(){
	for(size_t i=0;i<n;i++) std::cout<<data[i]<<" ";
	std::cout<<"\n";
	}
private:
	size_t n;
	double* data;
};

class myVector2{
public:
	// Note the explicit keyword in the constructor declaration
	explicit myVector2(size_t n_): n{n_}, data{new double[n_]{}} {std::cout<<"myVector2 constructor called\n";}
	void print(){
	for(size_t i=0;i<n;i++) std::cout<<data[i]<<" ";
	std::cout<<"\n";
	}
private:
	size_t n;
	double* data;
};

int explicit_constructor(){
	// implicit int to vector conversion is allowed (although it does not make any sense).
	myVector1 vec1 = 5;

	// implicit int to vector conversion is not allowed and results in error.
	// myVector2 vec2 = 5; // error

	// explicit conversion is ok
	myVector2 vec2 = (myVector2)6; // same as myVector2 vec2(6);

	vec1.print();
	vec2.print();
	return 0;
}
