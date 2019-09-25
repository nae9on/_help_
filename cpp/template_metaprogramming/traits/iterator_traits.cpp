/*
 * iterator_traits.cpp
 *
 *  Created on: Sep 25, 2019
 *      Author: akadar
 *
 * iterator_traits allow us to check which kind of iterator is provided.
 *
 * A nice example from [1], section 13.9 Type Functions
 * [1] Stroustrup, Bjarne. A Tour of C++. Chapter 4, Addison-Wesley Professional, 2018
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

// Sorting a container which supports random access iterator is trivial
template<typename T>
void mysort(T beg, T end, std::random_access_iterator_tag){
	std::sort(beg,end);
}

// Sorting a container which supports forward iterator is non-trivial
template<typename T>
void mysort(T beg, T end, std::forward_iterator_tag){
	using vt = typename T::value_type;
	std::vector<vt> vec{beg,end};
	std::sort(vec.begin(),vec.end());
	std::copy(vec.begin(),vec.end(),beg);
}

template<typename T>
void mysort(T beg, T end){
	using iterator_category = typename std::iterator_traits<T>::iterator_category;
	mysort(beg,end,iterator_category{}); // Note {}
}

int iterator_traits(){

	std::vector<int> vec{9,1,4,2,0};
	std::list<int> lst{9,1,4,2,0};
	int arr[5]{9,1,4,2,0};

	mysort(vec.begin(),vec.end());
	mysort(lst.begin(),lst.end());
	mysort(arr,arr+5);

	for(const auto& elem : vec) std::cout<<elem<<" ";
	std::cout<<"\n";
	for(const auto& elem : lst) std::cout<<elem<<" ";
	std::cout<<"\n";
	for(const auto& elem : arr) std::cout<<elem<<" ";

	return 0;
}
