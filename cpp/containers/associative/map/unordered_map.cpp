/*
 * unordered_map.cpp
 *
 *  Created on: Aug 27, 2019
 *      Author: akadar
 *
 * A std::unordered_map is an associative container that contains key-value pairs with unique keys.
 * Reference
 * [1] http://www.cplusplus.com/reference/unordered_map/unordered_map/
 *
 * Internally, the elements in the unordered_map are not sorted in any particular order with
 * respect to either their key or mapped values, but organized into buckets depending on their
 * hash values to allow for fast access to individual elements directly by their key values.
 *
 * As compared to maps, unordered_map containers are faster for accessing individual elements by
 * their key, although they are generally less efficient for range iteration through a subset of
 * their elements.
 *
 */

#include <iostream>
#include <unordered_map>

int unordered_map(){

	std::unordered_map<int,std::string> map;

	map.insert(std::make_pair(1989,"Ali"));
	map.insert(std::make_pair(1993,"Kaynat"));
	map.insert(std::make_pair(1962,"Mom"));

	// Note that output is not sorted by keys.
	// When unordered_map is changed to map, the output is sorted by keys.
	for(const auto& elem : map){
		std::cout<<elem.second<<" was born in year "<<elem.first<<"\n";
	}

	return 0;
}
