/*
 * type_deduction.cpp
 *
 *  Created on: 06 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <boost/type_index.hpp>

template<typename T>
void f(){
	std::cout<<boost::typeindex::type_id_with_cvr<T>().pretty_name()<<"\n";
}

int type_deduction(){

	f<int const* const>();

	int* x = nullptr;
	std::cout<<boost::typeindex::type_id_with_cvr<decltype(x)>().pretty_name()<<"\n";
	std::cout<<boost::typeindex::type_id_with_cvr<decltype((x))>().pretty_name()<<"\n";

	return 0;
}


