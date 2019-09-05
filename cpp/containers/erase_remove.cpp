/*
 * erase_remove.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: akadar
 *
 * Simple program which provides templated erase_remove for the following containers:
 * valarray, vector, deque, forward_list, list, map, set
 *
 * References:
 * Meyers, Scott (2001). Effective STL: 50 Specific Ways to Improve ...
 * https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
 *
 */

#include <iostream>
#include <algorithm>

#include <valarray>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

#include <map>
#include <set>

// Applicable for vector, deque, list
template<typename T, template<typename> class A, template<typename,typename> class C>
void erase_remove(C<T,A<T>>& ct){
	/*
	 * STL: how containers, iterators and algorithms collaborate ?
	 * A container knows how the elements are organized in memory.
	 * An algorithm knows how to access elements of a container using an iterator.
	 * An algorithm can modify the value of elements of a container but cannot
	 * allocate/deallocate memory. This separation of roles is essential for the
	 * working of STL.
	 *
	 * erase remove idiom
	 *
	 * remove doesn't actually delete elements from the container. It only shifts non-deleted
	 * elements forward on top of deleted elements. The key is to realize that remove() is
	 * designed to work on not a container but on any arbitrary forward iterator pair:
	 * that means it can't actually delete the elements, because an arbitrary iterator pair
	 * doesn't necessarily have the ability to delete elements.
	 *
	 * A call to remove is typically followed by a call to a container's erase method, which
	 * erases the unspecified values and reduces the physical size of the container to match
	 * its new logical size.
	 *
	 * Note: similar to remove, unique is also usually followed by a call to erase.
	 *
	 */

	using IT = typename C<T,A<T>>::iterator;
	IT begin_it = ct.begin();
	IT end_it = ct.end();
	IT it = std::remove_if(begin_it,end_it,[](const int& x)->bool{return x%2;});
	ct.erase(it, ct.end());
}

// partial template specialization for valarray
template<typename T>
void erase_remove(std::valarray<T>& ct){
	using IT = T*;
	IT begin_it = std::begin(ct);
	IT end_it = std::end(ct);
	IT it = std::remove_if(begin_it,end_it,[](const int& x)->bool{return x%2;});

	// Perhaps this can be improved?
	std::valarray<T> ct2;
	ct2.resize(it-begin_it,0);
	std::copy(begin_it,it,std::begin(ct2));
	ct.resize(it-begin_it,0);
	std::copy(std::begin(ct2),std::end(ct2),std::begin(ct));
}

// partial template specialization for forward_list
template<typename T, template<typename> class A>
void erase_remove(std::forward_list<T,A<T>>& ct){
	using IT = typename std::forward_list<T,A<T>>::iterator;
	IT begin_it = ct.begin();
	IT end_it = ct.end();
	IT it = std::remove_if(begin_it,end_it,[](const int& x)->bool{return x%2;});
	ct.erase_after(it, ct.cend());
}

// partial template specialization for map
template<typename K, typename V>
void erase_remove(std::map<K,V>& ct){
	using IT = typename std::map<K,V>::iterator;
	IT begin_it = ct.begin();
	IT end_it = ct.end();
	for(IT it = begin_it; it!=end_it; ++it){
		if(it->first%2){
			// References and iterators to the erased elements are invalidated.
			// Other references and iterators are not affected.
			ct.erase(it);
		}
	}
}

// partial template specialization for set
template<typename K>
void erase_remove(std::set<K>& ct){
	using IT = typename std::set<K>::iterator;
	IT begin_it = ct.begin();
	IT end_it = ct.end();
	for(IT it = begin_it; it!=end_it; ++it){
		if(*it%2){
			// References and iterators to the erased elements are invalidated.
			// Other references and iterators are not affected.
			ct.erase(it);
		}
	}
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

	std::valarray<int> varr({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, varr = ",varr);
	erase_remove(varr);
	print_container("After erase remove, varr = ",varr);

	std::vector<int> vec({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, vec = ",vec);
	erase_remove(vec);
	print_container("After erase remove, vec = ",vec);

	std::deque<int> deq({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, deq = ",deq);
	erase_remove(deq);
	print_container("After erase remove, deq = ",deq);

	std::forward_list<int> flist({3,1,2,6,4,8,9,10});
	print_container("Before erase remove, flist = ",flist);
	erase_remove(flist);
	print_container("After erase remove, flist = ",flist);

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
