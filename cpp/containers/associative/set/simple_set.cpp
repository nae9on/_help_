/*
 * simple_set.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: akadar
 *
 * A std::set is a sorted associative container that contains unique keys. It is similar
 * to std::map and is usually implemented using BST's. However, there are two main
 * differences:
 * 1. Unlike std::map, there is no value associated to the unique key.
 * 2. The value of the elements in a set cannot be modified once in the container
 *    (the elements are always const), but they can be inserted or removed from the
 *    container.
 * 3. Unlike map, set does not support operator[] access. In fact map and unordered_map
 *    are the only associative containers which supports operator[].
 *
 * Reference
 * [1] http://www.cplusplus.com/reference/set/set/
 *
 */

#include <iostream>
#include <set>

int simple_set(){

	std::cout<<"In main simple_set.cpp\n";

	std::set<double> setd({5,3,7,9,2});

	for(const auto& elem : setd) std::cout<<elem<<" ";

	return 0;
}


