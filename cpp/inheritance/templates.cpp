/*
 * templates.cpp
 *
 *  Created on: Aug 10, 2019
 *      Author: akadar
 *
 *  Example demonstrating multiple inheritance using templates.
 */

#include <iostream>

class X{
public:
	void print_name(){
		std::cout<<"I am X\n";
	}
};

template<typename T> class Y: public T{
public:
	void print_name(){
		std::cout<<"I am Y\n";
		T::print_name();
	}
};

template<typename T> class Z: public T{
public:
	void print_name(){
		std::cout<<"I am Z\n";
		T::print_name();
	}
};

template<typename T> class YZ: public T{
public:
	void print_name(){
		std::cout<<"I am YZ\n";
		T::print_name();
	}
};

int templates(){

	YZ<Y<X>> yz1;
	yz1.print_name();

	YZ<Z<X>> yz2;
	yz2.print_name();

	return 0;
}
