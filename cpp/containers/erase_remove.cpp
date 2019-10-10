/*
 * erase_remove.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: akadar
 *
 * Simple program which provides templated erase_remove for the following STL containers:
 * vector, deque, string, forward_list, list, map and set.
 *
 * All the elements of a container which satisfy a predicate condition must be removed.
 *
 * STL: how containers, iterators and algorithms collaborate?
 * A container knows how the elements are organized in memory. An algorithm knows how to
 * access elements of a container using iterator's. Note that there is no way to know
 * the container type from the iterator type. Therefore, an algorithm can modify the value
 * of elements of a container but cannot allocate/deallocate memory. This separation of roles
 * is essential for the working of STL.
 *
 * erase remove idiom
 *
 * remove algorithm doesn't actually delete elements from a container. It only shifts non-deleted
 * elements forward on top of deleted elements. The key is to realize that remove is designed to
 * work on not a container but on any arbitrary forward iterator pair. That means it can't actually
 * delete the elements (for the reason mentioned above).
 *
 * A call to remove is typically followed by a call to a container's erase method, which
 * erases the unspecified values and reduces the physical size of the container to match
 * its new logical size.
 *
 * Note: similar to remove, unique is also usually followed by a call to erase.
 * Note: erase invalidates iterators and references at and after the point of the erase,
 * including the end() iterator.
 *
 * References:
 * Meyers, Scott (2001). Effective STL: 50 Specific Ways to Improve ...Scott#9,#32,#44
 * https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
 *
 */

#include <iostream>
#include <algorithm>

#include <vector>
#include <deque>
#include <string>
#include <forward_list>
#include <list>

#include <map>
#include <set>

// Predicate class for the function object
class isOdd{
public:
	template<typename T>
	bool operator()(const T& elem){
		return elem%2;
	}
};

// Applicable for vector, deque, string
template<typename T>
void erase_remove(T& ct){
	auto it = std::remove_if(ct.begin(),ct.end(),(isOdd()));
	ct.erase(it, ct.end());
	// ct.erase_if is available in C++20!
}

// Partial template specialization for list (also applicable to forward_list)
template<typename T>
void erase_remove(std::list<T>& ct){
	ct.remove_if((isOdd()));
	// ct.erase_if is available in C++20!
	// ct.erase_if and ct.remove_if are equivalent for a list
}

// partial template specialization for map
// map is a node based container and therefore erasing an element is straight forward
template<typename K, typename V>
void erase_remove(std::map<K,V>& ct){
	for(auto it = ct.begin(); it!=ct.end();){
		if(isOdd()(it->first)){
			// References and iterators to the erased elements are invalidated.
			// Other references and iterators are not affected. Scott#9
			ct.erase(it++);
		}else
		{
			++it;
		}
	}
	// ct.erase_if is available in C++20!
}

// partial template specialization for set
// set is a node based container and therefore erasing an element is straight forward
template<typename K>
void erase_remove(std::set<K>& ct){
	for(auto it = ct.begin(); it!=ct.end();){
		if(isOdd()(*it)){
			// References and iterators to the erased elements are invalidated.
			// Other references and iterators are not affected. Scott#9
			ct.erase(it++);
		}else
		{
			++it;
		}
	}
	// ct.erase_if is available in C++20!
}

template<typename T>
void print_container(const std::string& s, T& ct){
	std::cout<<s<<" ";
	for(const auto& v : ct) {std::cout<<v<<" ";}
	std::cout<<std::endl;
}

// partial template specialization for map
template<typename K, typename V>
void print_container(const std::string& s, std::map<K,V>& ct){
	std::cout<<s<<" ";
	for(const auto& v : ct) {std::cout<<v.first<<" ";}
	std::cout<<std::endl;
}

int erase_remove(){

	std::vector<int> vec({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, vec = ",vec);
	erase_remove(vec);
	print_container("After erase remove, vec = ",vec);

	std::list<int> llist({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, llist = ",llist);
	erase_remove(llist);
	print_container("After erase remove, llist = ",llist);

	std::map<int,std::string> mp({
				std::make_pair(3,"C"),
				std::make_pair(1,"A"),
				std::make_pair(2,"B"),
				std::make_pair(6,"F"),
				std::make_pair(4,"D"),
				std::make_pair(8,"H"),
				std::make_pair(9,"I"),
				std::make_pair(10,"J")
	});
	print_container("Before erase remove, mp = ",mp);
	erase_remove(mp);
	print_container("After erase remove, mp = ",mp);

	std::set<int> st({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, st = ",st);
	erase_remove(st);
	print_container("After erase remove, st = ",st);

	return 0;
}
