/*
 * value_type.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: akadar
 *
 *  Demonstrating the use of type alias value_type defined in STL containers.
 *  value_type is used to determine the type of the values held by the container.
 */

#include <iostream>
#include <vector>
#include <deque>

template<typename C, typename VT = typename C::value_type, typename VEC = std::vector<VT>>
VEC to_vector(const C& c){
	VEC vec;
	// copy c to vec
	return vec;
}

int value_type(){

	std::deque<int> dek{1,2,3};

	auto vec = to_vector(dek);

	(void) vec; // cast to void to suppress warning

	return 0;
}
