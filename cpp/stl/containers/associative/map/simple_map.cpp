/*
 * simple_map.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 *
 * A std::map is a sorted associative container that contains std::pair<const Key, Value>
 * with unique keys. It is an ordered container with items sorted by using a comparison
 * function object type.
 *
 * Maps are usually implemented as red-black trees (self-balancing binary search trees).
 * References
 * [1] http://www.cplusplus.com/reference/map/map/
 * [2] https://www.youtube.com/watch?v=qvZGUFHWChY
 */

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::make_pair
#include "biography.h"
#include <functional> // for std::greater

int simple_map()
{
	// Note that the default comparator is std::less<Key> (a function object).
	// Note that the template argument (std::string) can be auto-deduced from C++14 onwards.
	std::map<std::string,biography,std::greater<std::string>> myMap;

	// Insert new key-value pairs.
	myMap.insert(std::make_pair("Ali",biography()));
	myMap.insert(std::make_pair("Kaynat",biography()));
	myMap.insert(std::make_pair("Mom",biography()));

	// Change value associated to a particular key.
	auto it = myMap.find("Ali");
	if(it!=myMap.end()) {
		it->second.setName("Ali Hussain Kadar");
		it->second.setAge(29);
	}

	/*
	 * myMap.insert will only insert if the key does not exist in the map.
	 * insert returns a pair consisting of an iterator to the inserted element
	 * (or to the element that prevented the insertion) and a bool denoting whether
	 * the insertion took place. The return value of insert can thus be used
	 * to check if the insertion took place.
	 */

	// Example: try to insert an already existing key.
	if(!myMap.insert(std::make_pair("Ali",biography("x",100))).second){
		std::cout<<"Key Ali already exists.\n";
	}

	// Example: try to add a new key.
	if(myMap.insert(std::make_pair("Dad",biography())).second) {
		std::cout<<"Adding key Dad for the first time.\n";
	}

	// Be careful of accidently creating a key value pair as
	// Never use operator[] to insert a new pair (refer ESTL#24) because of efficiency reasons
	myMap["Accidental name"].setAge(100);

	// In order to check if a key exists in the map use find member function.
	// Accessing key AliK which does not exist would do nothing.
	if(myMap.find("AliK")==myMap.cend()) {
		std::cout << "AliK key does not exist.\n";
	}

	// Accessing key Dad.
	if(myMap.find("Dad")!=myMap.end()) {
		std::cout << "Dad key exists.\n";
	}

	std::cout<<"\n";

	// Note that map traversal follows the sort order
	for (const auto& t : myMap)
	{
		std::cout<<t.first<<"\n";
		t.second.printInfo();
	}

	return 0;
}
