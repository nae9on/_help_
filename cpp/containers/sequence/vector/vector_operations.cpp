/*
 * vector_operations.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: akadar
 *
 *  References:
 *  https://en.cppreference.com/w/cpp/container/vector
 *
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm> // std::copy
#include <iterator> // for std::back_inserter, std::reverse, std::sort

template<typename T>
void print_vec(T vec_){
	for(const auto& v : vec_) { std::cout<<v<<" ";}
}

int vector_operations(){

	// Declaration and initialization
	std::vector<int> vec1; // empty vector
	std::vector<int> vec2(5,10); // vector of size 5 filled with 10's
	std::initializer_list<int> init = {7,4,12,34,3};
	std::vector<int> vec3(init); // vector of size 5 filled using initializer_list

	// size, capacity and max size
	std::vector<int> vec100(100,10); // initially size = capacity = 100
	vec100.push_back(10); // after push, size = 101, capacity = 200
	printf("vec100: size = %zu, capacity = %zu, max size = %zu\n"
			,vec100.size(),vec100.capacity(),vec100.max_size());

	// shrink vector capacity to its size
	vec100.shrink_to_fit();
	printf("After shrink vec100: size = %zu, capacity = %zu\n"
			,vec100.size(),vec100.capacity());

	// reserve memory when known a priori
	vec100.reserve(1000);
	printf("After call to reserve vec100: size = %zu, capacity = %zu\n"
			,vec100.size(),vec100.capacity());

	// clear vector
	vec100.clear(); // erases all elements but keeps the capacity the same
	printf("After call to clear vec100: size = %zu, capacity = %zu\n"
			,vec100.size(),vec100.capacity());

	// Check emptiness
	if(vec1.cbegin()==vec1.cend()) std::cout<<"Empty vector vec1\n";

	// Check emptiness and size
	if(!vec2.empty()) std::cout<<"vec2 has size = "<<vec2.size()<<"\n";

	// Traversal using range-for
	std::cout<<"vec2 = ";
	print_vec(vec2);
	std::cout<<"\nvec2 = ";
	for(const int& v : vec2) { std::cout<<v<<" ";}

	// Traversal using const iterator
	std::cout<<"\nvec2 = ";
	for(std::vector<int>::const_iterator it = vec2.cbegin(); it!=vec2.cend(); ++it){
		std::cout<<*it<<" ";
	}

	// Copying a vector
	std::cout<<"\nvec3 = ";
	print_vec(vec3);
	std::cout<<"\nvec3 copied to vec2";
	std::copy(vec3.cbegin(),vec3.cend(),vec2.begin());
	std::cout<<"\nvec2 = ";
	print_vec(vec2);

	// Back insertion
	/*
	 * std::back_inserter is a function template which returns a back-insert iterator.
	 * A back-insert iterator is a special type of output iterator designed to allow
	 * algorithms that usually overwrite elements (such as copy) to instead insert new
	 * elements automatically at the end of the container.
	 */
	std::cout<<"\nvec3 copied to empty vec1 using back_inserter";
	std::copy(vec3.cbegin(),vec3.cend(),std::back_inserter(vec1));
	std::cout<<"\nvec1 = ";
	print_vec(vec1);

	// Note vec3.insert can achieve the same with slightly better performance.
	std::cout<<"\nvec3 copied to empty vec1 using insert";
	vec1.clear();
	vec1.insert(vec1.cend(),vec3.cbegin(),vec3.cend());
	std::cout<<"\nvec1 = ";
	print_vec(vec1);

	// Concatenating two vectors using std::back_inserter
	std::vector<int> vecof10(5,10);
	std::copy(vec3.cbegin(),vec3.cend(),std::back_inserter(vecof10));
	std::cout<<"\nvecof10 = vecof10 + vec1 = ";
	print_vec(vecof10);

	// Reversing a vector
	// Reverse takes two bidirectional iterators and returns void
	std::reverse(vec3.begin(),vec3.end());
	std::cout<<"\nReversed vec3 = ";
	print_vec(vec3);

	// Sorting a vector
	std::sort(vec3.begin(),vec3.end());
	std::cout<<"\nSorted vec3 = ";
	print_vec(vec3);

	return 0;
}