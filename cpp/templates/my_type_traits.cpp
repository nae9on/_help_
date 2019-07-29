/*
 * my_type_traits.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: akadar
 *
 * Reference: http://blog.aaronballman.com/2011/11/a-simple-introduction-to-type-traits
 */

//#define NDEBUG // defining this macro will disable assertion at run-time

#include <iostream>
#include <string>
#include <assert.h>

// Simple example of a templated increment function which is supposed to
// increment only ints.
template<typename T> void increment(T& x){
	++x;
}

template<> void increment(char& x){
	assert(false && "Illegal to increment char");
}

template<> void increment(double& x){
	assert(false && "Illegal to increment double");
}
// what if a user-defined type is passed?

// Better version of templated increment function
template <typename T>
struct is_incrementable {
  static const bool value = false;
};

template <>
struct is_incrementable<int> {
  static const bool value = true;
};

template<typename T> void better_increment(T& x){
	assert(is_incrementable<T>::value && "Illegal to increment");
	++x;
}

// Best version of templated increment function
template <typename T>
struct is_incrementable2 {
  static const bool value = std::is_integral< T >::value && sizeof( T ) >= 2;
};

template<typename T> void smart_increment(T& x){
	assert(is_incrementable2<T>::value && "Illegal to increment");
	++x;
}

int main(){

	std::cout<<"In main\n";

	int i = 1;
	short sh = 1;
	char c  = 'a';
	float f = 3.0;
	double d = 7.0;

	increment(i); // OK
	//increment(sh); // OK
	//increment(c); // OK run-time assertion fail
	increment(f); // NOT OK as float is not an int
	//increment(d); // OK run-time assertion fail

	better_increment(i); // OK
	//better_increment(sh); // NOT OK as short is an int
	//better_increment(c); // OK run-time assertion fail
	//better_increment(f); // OK run-time assertion fail
	//better_increment(d); // OK run-time assertion fail

	smart_increment(i); // OK
	smart_increment(sh); // OK
	//smart_increment(c); // OK run-time assertion fail
	//smart_increment(f); // OK run-time assertion fail
	//smart_increment(d); // OK run-time assertion fail

    std::cout<<"Done main";
	return 0;
}
