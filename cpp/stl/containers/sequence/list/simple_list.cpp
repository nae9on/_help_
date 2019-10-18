/*
 * simple_list.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: akadar
 *
 * References
 * [1] http://www.cplusplus.com/reference/list/list/
 */

#include <iostream>
#include <list>
#include <iterator>

int simple_list(){

	std::list<int> data{1,2,3,4,5,6};

	std::list<int> patch{-1,-2,-3};

	// Move patch to middle of data using splice member function (very special)

	// Since list does not provide random-access-iterator! the iterator to the middle of the list
	// should be obtained by list traversal.
	std::list<int>::iterator pos{data.begin()};
	for(size_t i = 0; i<data.size()/2; ++i) ++pos;

	data.splice(pos,patch,patch.begin(),patch.end()); // Scott#4

	for(const auto& elem : data) std::cout<<elem<<" ";

	std::cout<<"\n";

	return 0;
}
