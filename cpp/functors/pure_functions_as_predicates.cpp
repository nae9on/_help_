/*
 * pure_functions_as_predicates.cpp
 *
 *  Created on: 31 Oct 2019
 *      Author: ahkad
 *
 * f(x,y) is a pure function if its return value can change only when x and/or y changes.
 *
 * Reference:
 * Item 39, Effective STL, Scott Meyers
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

unsigned t = 1;

/*
 * isLessThanTime is not a pure function and thus is a bad choice for being
 * a predicate
 */
bool isLessThanTime(unsigned item){
	return (item<t);
}

int pure_functions_as_predicates(){

	using IT = std::vector<unsigned>::const_iterator;

	std::vector<unsigned> vec(10);
	std::iota(vec.begin(),vec.end(),1);

	std::cout<< std::count_if<IT, bool(*)(unsigned)>(
						vec.cbegin(), vec.cend(), isLessThanTime) << "\n";
	++t;

	std::cout<< std::count_if<IT, bool(*)(unsigned)>(
					vec.cbegin(), vec.cend(), isLessThanTime) << "\n";

	return 0;
}

