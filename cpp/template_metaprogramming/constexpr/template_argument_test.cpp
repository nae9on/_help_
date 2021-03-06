/*
 * template_argument_test.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: akadar
 */

#include <iostream>
#include <string>

template<typename T> bool odd_or_even(T x){
	constexpr bool checkInt = std::is_same<T, int>::value;
	// static_assert expects a bool constexpr
	static_assert(checkInt,"template argument is not int");
	return x%2;
}

int template_argument_test(){

	int x = 10;
	std::cout << (odd_or_even(x) ? "Is odd\n" : "Is even\n");

	float y = 10;
	//std::cout << (odd_or_even(y) ? "Is odd" : "Is even"); // Error static assertion failed

	std::cout<<"y = "<<y<<"\n";

	return 0;
}


