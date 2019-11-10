/*
 * predicate_pass_by_copy_or_ref.cpp
 *
 *  Created on: 31 Oct 2019
 *      Author: ahkad
 *
 * How to pass a predicate to an algorithm? by copy or by reference?
 * Note: a predicate can be either a plain function or a function object (including lambdas).
 *
 * Reference:
 * Item 38 "Design functor classes for pass-by-value", Effective STL, Scott Meyers
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
	isDiv(const isDiv& e){
		divisor = e.divisor;
		std::cout<<"Copy constructor called\n";
	}
inline bool operator()(unsigned item) const{
	return (item%divisor==0);
}
private:
unsigned divisor; // state should be as light-weight as possible
};

int predicate_pass_by_copy_or_ref(){

	using IT = std::vector<unsigned>::const_iterator;

	std::vector<unsigned> vec(15);
	std::iota(vec.begin(),vec.end(),1);

	isDiv is3(3);

	// passing a plain function (as pass by copy)
	// a function is always passed as a function pointer (which is passed by copy)
	std::cout<< std::count_if<IT, bool(*)(unsigned)>(vec.cbegin(), vec.cend(), isDiv3) << "\n";

	// passing function object as pass by copy - preferred as default by the standard
	std::cout<< std::count_if(vec.cbegin(), vec.cend(), is3) << "\n";
	// Note multiple copies can be created by STL algorithms (not controlled by the user).
	// Therefore, the functor class must be as light-weight as possible.

	// passing function object as pass by reference - not preferred by the standard
	std::cout<< std::count_if<IT, isDiv&>(vec.cbegin(), vec.cend(), is3) << "\n";

	return 0;
}
