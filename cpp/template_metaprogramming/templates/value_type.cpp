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
	for(const auto& e : c) vec.push_back(e);
	return vec;
}

int value_type(){

	std::deque<int> dek{1,2,3};
	std::initializer_list<int> initlist{4,5,6};

	auto vec1 = to_vector(dek);
	auto vec2 = to_vector(initlist);

	for(const auto& e : vec1) std::cout<<e<<" ";

	std::cout<<std::endl;

	for(const auto& e : vec2) std::cout<<e<<" ";

	std::cout<<std::endl;

	return 0;
}
