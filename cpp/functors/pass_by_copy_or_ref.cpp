/*
 * pass_by_copy_or_ref.cpp
 *
 *  Created on: 31 Oct 2019
 *      Author: ahkad
 *
 * Reference:
 * Item 38, Effective STL, Scott Meyers
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

bool isDiv3(unsigned item){
	return (item%3==0);
}

class isDiv{
public:
	isDiv() = delete;
	isDiv(unsigned divisor_): divisor(divisor_){}
bool operator()(unsigned item) const{
	return (item%divisor==0);
}
private:
unsigned divisor;
};

int pass_by_copy_or_ref(){

	using IT = std::vector<unsigned>::const_iterator;

	std::vector<unsigned> vec(10);
	std::iota(vec.begin(),vec.end(),1);

	isDiv is3(3);

	// passing pure function (as pass by copy)
	// a function is always passed as a function pointer which is passed by copy
	// a predicate can be either a function or a function object
	std::cout<< std::count_if<IT, bool(*)(unsigned)>(
					vec.cbegin(), vec.cend(), isDiv3) << "\n";

	// passing function object (as pass by copy) - preferred by the standard
	std::cout<< std::count_if<IT, isDiv>(vec.cbegin(),
					vec.cend(), is3) << "\n";

	// passing function object (as pass by reference) - not preferred by the standard
	std::cout<< std::count_if<IT, isDiv&>(vec.cbegin(),
					vec.cend(), is3) << "\n";

	return 0;
}
