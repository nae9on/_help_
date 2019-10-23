/*
 * iterator_traits.cpp
 *
 *  Created on: Sep 25, 2019
 *      Author: akadar
 *
 * iterator_traits allow us to check which kind of iterator is provided.
 *
 * A nice example from [1], section 13.9 Type Functions
 *
 * [1] Stroustrup, Bjarne. A Tour of C++. Chapter 4, Addison-Wesley Professional, 2018
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>

template<typename T>
struct is_sortable{
	static constexpr bool value = false;
};

template<>
struct is_sortable<std::forward_iterator_tag>{
	static constexpr bool value = true;
};

template<>
struct is_sortable<std::bidirectional_iterator_tag>{
	static constexpr bool value = true;
};

template<>
struct is_sortable<std::random_access_iterator_tag>{
	static constexpr bool value = true;
};

// Sorting a container which supports forward iterator is non-trivial
template<typename T1, typename T2>
void mysort(T1 beg, T1 end, const std::forward_iterator_tag& obj){
	using vt = typename T1::value_type;
	std::vector<vt> vec{beg,end};
	std::sort(vec.begin(),vec.end());
	std::copy(vec.begin(),vec.end(),beg);
}

// Sorting a container which supports bidirectional iterator is non-trivial
template<typename T>
void mysort(T beg, T end, const std::bidirectional_iterator_tag& obj){
	using vt = typename T::value_type;
	std::vector<vt> vec{beg,end};
	std::sort(vec.begin(),vec.end());
	std::copy(vec.begin(),vec.end(),beg);
}

// Sorting a container which supports random access iterator is trivial
template<typename T>
void mysort(T beg, T end, std::random_access_iterator_tag){
	std::sort(beg,end);
}

// mysort function aims to sort the range [beg, end) defined by the iterators beg and end
template<typename T>
void mysort(T beg, T end)
{
	using my_iterator_category = typename std::iterator_traits<T>::iterator_category;

	static_assert(is_sortable<my_iterator_category>::value,"not sortable");

	mysort(beg,end,my_iterator_category()); // Note my_iterator_category is a struct
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

	std::ostream_iterator<int> beg1(std::cout);
	std::ostream_iterator<int> end1(beg1);
	std::istream_iterator<int> beg2(std::cin);
	std::istream_iterator<int> end2{};

	//mysort(beg1,end1);
	//mysort(beg2,end2);

	return 0;
}
