/*
 * map_operations.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: akadar
 */

#include <iostream>
#include <map>
#include "biography.h"
#include <utility>
#include <string>

template<typename T>
void print_map(T map_){
	for(const auto& v : map_) {std::cout<<v.first<<" "<<v.second.getName()<<" ";}
}

int main(){

	// Declaration and initialization
	std::pair<std::string,biography> p = std::make_pair("a",biography("apple",1));
	std::map<std::string,biography> map1; // empty map
	std::map<std::string,biography> map2 = {std::make_pair("a",biography("apple",1)),
			std::make_pair("d",biography("dog",2)),
			std::make_pair("c",biography("cat",3))};

	// size and max size. It does not have a concept of capacity and reserve as std::vector.
	printf("map1: size = %zu, max size = %zu\n",map1.size(),map1.max_size());
	printf("map2: size = %zu, max size = %zu\n",map2.size(),map2.max_size());

	// Check emptiness
	if(map1.cbegin()==map1.cend()) std::cout<<"Empty map1\n";

	// Check emptiness and size
	if(!map2.empty()) std::cout<<"map2 has size = "<<map2.size()<<"\n";

	// Traversal using range-for
	std::cout<<"map2 = ";
	print_map(map2);
	std::cout<<"\nvec2 = ";
	for(const std::pair<std::string,biography> v : map2) {std::cout<<v.first<<" "<<v.second.getName()<<" ";}

	// Traversal using const iterator
	std::cout<<"\nmap2 = ";
	for(std::map<std::string,biography>::const_iterator it = map2.cbegin(); it!=map2.cend(); ++it){
		{std::cout<<it->first<<" "<<it->second.getName()<<" ";}
	}

	// Copying a map
	// std::copy takes two input iterator's, one output iterator and returns an output iterator
	std::cout<<"\nmap2 copied to map1";
	map1.insert(map2.cbegin(),map2.cend());
	std::cout<<"\nmap1 = ";
	print_map(map1);

	return 0;
}


