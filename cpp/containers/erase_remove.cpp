/*
 * erase_remove.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: akadar
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
	ct.erase(it, ct.cend());
}

// partial template specialization for valarray
template<typename T>
void erase_remove(std::valarray<T>& ct){
	T* begin_it = std::begin(ct);
	T* end_it = std::end(ct);
	T* it = std::remove_if(begin_it,end_it,[](const int& x)->bool{return x%2;});

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

template<typename T>
void print_container(std::string s, T& Ct){
	std::cout<<s<<" ";
	for(const auto& v : Ct) {std::cout<<v<<" ";}
	std::cout<<std::endl;
}

int main(){

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

	return 0;
}
