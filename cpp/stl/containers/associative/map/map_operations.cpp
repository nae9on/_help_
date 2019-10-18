/*
 * map_operations.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: akadar
 */

#include <iostream>
#include <map>
#include "biography.h"
#include <utility> // defines std::pair, std::make_pair
#include <string>
#include <algorithm> // std::copy
#include <iterator> // for std::inserter

template<typename T>
void print_map(T map_){
	for(const auto& v : map_) {std::cout<<v.first<<" "<<v.second.getName()<<" ";}
}

int map_operations(){

	// Declaration and initialization
	std::pair<std::string,biography> p = std::make_pair("a",biography("apple",1));
	std::map<std::string,biography> map1; // empty map
	std::map<std::string,biography> map2 = {std::make_pair("a",biography("apple",1)),
			std::make_pair("d",biography("dog",2)),
			std::make_pair("c",biography("cat",3))};

	// size and max size.
	// Note: std::map does not have concepts of capacity and reserve as std::vector.
	printf("map1: size = %zu, max size = %zu\n",map1.size(),map1.max_size());
	printf("map2: size = %zu, max size = %zu\n",map2.size(),map2.max_size());

	// map2.clear() // will erase all elements making size = 0.

	// Check emptiness
	if(map1.cbegin()==map1.cend()) std::cout<<"Empty map1\n";

	// Check emptiness and size
	if(!map2.empty()) std::cout<<"map2 has size = "<<map2.size()<<"\n";

	// Traversal using range-for
	std::cout<<"map2 = ";
	print_map(map2);
	std::cout<<"\nmap2 = ";
	for(const auto& v : map2){
		std::cout<<v.first<<" "<<v.second.getName()<<" ";
	}

	// Traversal using const iterator
	std::cout<<"\nmap2 = ";
	for(std::map<std::string,biography>::const_iterator it = map2.cbegin(); it!=map2.cend(); ++it){
		std::cout<<it->first<<" "<<it->second.getName()<<" ";
	}

	// Copying a range of elements to a map does not make sense.
	// However, inserting a range of elements in a map makes sense.
	std::cout<<"\nmap2 copied to map1";
	map1.insert(map2.cbegin(),map2.cend());
	// std::copy(map2.cbegin(),map2.cend(),std::inserter(map1, map1.end())); // Awful solution
	std::cout<<"\nmap1 = ";
	print_map(map1);

	return 0;
}
