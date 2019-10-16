/*
 * modifying_stl_algo.cpp
 *
 *  Created on: Oct 15, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <set>

#include <algorithm>

template<typename T>
class square{
	public:
	square() = default;
	T operator()(T x){
		return x*x;
	}
};

template<typename T>
class sum{
	public:
	sum() = default;
	T operator()(T x, T y){
		return x+y;
	}
};

int modifying_stl_algo(){

	std::vector<int> myvec{10,1,4,5,9,9,11,4,5,9,9};
	std::set<int> myset(myvec.cbegin(),myvec.cend());

	for(const auto& elem : myvec) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";

	/*
	 * std::transform
	 * Applies an operation sequentially to the elements of one (1) or two (2) ranges and stores
	 * the result in the range that begins at result.
	 *
	 * returns an iterator pointing to the element that follows the last element written in the
	 * result sequence.
	 *
	 * The function allows for the destination range to be the same as one of the input ranges
	 * to make transformations in place.
	 */
	std::vector<int> veccopy1(myvec.size());
	auto it = std::transform(myvec.cbegin(),myvec.cend(),veccopy1.begin(),(square<int>())); //usage 1
	it = std::transform(myvec.cbegin(),myvec.cend(),veccopy1.cbegin(),veccopy1.begin(), //usage 2
																  (sum<int>()));
	for(const auto& elem : veccopy1) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";




	/*
	 * std::copy
	 * Copies the elements in the range [first,last) into the range beginning at result.
	 *
	 * std::reverse_copy
	 * Copies the elements in the range [first,last) to the range beginning at result, but in
	 * reverse order.
	 *
	 * returns an output iterator pointing to the end of the copied range, which contains the
	 * same elements in reverse order.
	 *
	 * std::reverse
	 * Reverses the order of the elements in the range [first,last).
	 *
	 * std::unique_copy
	 * Copies the elements in the range [first,last) to the range beginning at result, except
	 * consecutive duplicates (elements that compare equal to the element preceding). Only the
	 * first element from every consecutive group of equivalent elements in the range [first,last)
	 * is copied. The comparison between elements is performed by either applying operator==, or
	 * the template parameter pred (for the second version) between them.
	 */
	std::vector<int> veccopy2(myvec.size());
	it = std::reverse_copy(myvec.cbegin(),myvec.cend(),veccopy2.begin());
	for(const auto& elem : veccopy2) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";




	/*
	 * std::remove, std::remove_if, std::unique - already familiar
	 *
	 * std::replace
	 * Assigns new_value to all the elements in the range [first,last) that compare equal to
	 * old_value.
	 *
	 * std::swap (similarly std::iter_swap)
	 * Exchanges the values of a and b. However, it involves a copy construction and two assignment
	 * operations, which may not be the most efficient way of swapping the contents of classes that
	 * store large quantities of data, since each of these operations generally operate in linear
	 * time on their size.
	 *
	 * std::swap_ranges
	 * Exchanges the values of each of the elements in the range [first1,last1) with those of their
	 * respective elements in the range beginning at first2.
	 */
	std::vector<int> vec1{10,1,4,5,9,9,11,4,5,9,9};
	std::vector<int> vec2(vec1.size()); std::iota(vec2.begin(),vec2.end(),1);
	std::swap_ranges(vec1.begin(),vec1.end(),vec2.begin());
	for(const auto& elem : vec1) std::cout<<elem<<" ";
	std::cout<<"\n";
	for(const auto& elem : vec2) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";




	/*
	 * std::rotate
	 * Rotates the order of the elements in the range [first,last), in such a way that the element
	 * pointed by middle becomes the new first element.
	 *
	 */
	std::rotate(vec1.begin(),vec1.begin()+1,vec1.end());
	for(const auto& elem : vec1) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";




	/*
	 * Rearranges the elements from the range [first,last), in such a way that all the elements for
	 * which pred returns true precede all those for which it returns false. The iterator returned
	 * points to the first element of the second group. The relative ordering within each group is
	 * not necessarily the same as before the call. See stable_partition for a function with a
	 * similar behavior but with stable ordering within each group.
	 */
	//std::partition(myvec.begin(),myvec.end(),[](int x){return x%2;});
	std::stable_partition(myvec.begin(),myvec.end(),[](int x){return x%2;});
	for(const auto& elem : myvec) std::cout<<elem<<" ";
	std::cout<<"\n**************************************\n";

	return 0;
}
