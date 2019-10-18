/*
 * simple_vector.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: akadar
 *
 * References
 * [1] http://www.cplusplus.com/reference/vector/vector/
 */

#include <iostream>
#include <vector>

template<typename T> void print(T t){
	std::cout<<"forward traversal using const_iterator\n";
	for(typename T::const_iterator it = t.cbegin(); it != t.cend(); ++it){
		std::cout<<*it<<" ";
	}
	std::cout<<"\n\n";
}

template<typename T> void print_backward(T t){
	std::cout<<"backward traversal using const_iterator\n";
	//for(typename T::const_iterator it = t.cend()-1; it >= t.cbegin(); --it){
	for(typename T::const_reverse_iterator it = t.crbegin(); it != t.crend(); ++it){
		std::cout<<*it<<" ";
	}
	std::cout<<"\n\n";
}

// find all occurrence
template<typename C, typename IT = typename C::const_iterator, typename T = typename C::value_type>
std::vector<size_t> all_occurence(C t, T a){
	std::vector<size_t> index;
	size_t itr{0};
	for(IT it = t.cbegin(); it != t.cend(); ++it, ++itr){
		if(*it==a) index.push_back(itr);
	}
	return index;
}

int simple_vector(){

	std::initializer_list<int> l0 {7,8,9,4,3,2,1,3};
	std::vector<int> x{l0};

	print(x);
	print_backward(x);

	auto pos = all_occurence(x, 3);
	std::cout<<"Occurence of 3 are at position\n";
	print(pos);

	return 0;
}
