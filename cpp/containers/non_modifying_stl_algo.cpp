/*
 * non_modifying_stl_algo.cpp
 *
 *  Created on: Oct 14, 2019
 *      Author: akadar
 */

#include <iostream>

#include <vector>
#include <set>

#include <algorithm>

// functor class
class myprint{
public:
	myprint() = default;
	template<typename T>
	void operator()(T& elem) const{
		std::cout<<elem<<" ";
	}
};

int non_modifying_stl_algo(){

	std::vector<int> myvec{10,1,4,5,9,9,11,4,5,9,9};
	std::set<int> myset(myvec.cbegin(),myvec.cend());

	/*
	 * std::for_each
	 * Applies predicate function to each of the elements in the range [first,last).
	 *
	 * clearly input iterators will suffice.
	 */
	std::for_each(myvec.cbegin(),myvec.cend(),(myprint()));
	std::cout<<"\n";
	std::for_each(myset.cbegin(),myset.cend(),(myprint()));
	std::cout<<"\n";
	std::cout<<"**************************************\n";




	/*
	 * std::find
	 * Returns an iterator to the first element in the range [first,last) that compares equal
	 * to a value. If no such element is found, the function returns last.
	 *
	 * std::find_if
	 * Returns an iterator to the first element in the range [first,last) for which pred returns
	 * true. If no such element is found, the function returns last.
	 *
	 * clearly input iterators will suffice.
	 */
	auto it1 = std::find(myvec.cbegin(),myvec.cend(),4);
	if(it1!=myvec.cend())
		std::cout<<"found in vector!\n";
	else
		std::cout<<"not found in vector!\n";

	auto it2 = myset.find(40); // prefer find member function for sets
	if(it2!=myset.cend())
		std::cout<<"found in set!\n";
	else
		std::cout<<"not found in set!\n";
	std::cout<<"**************************************\n";




	/*
	 * std::search
	 * Searches the range [first1,last1) for the first occurrence of the sequence defined by
	 * [first2,last2), and returns an iterator to its first element, or last1 if no occurrences
	 * are found.
	 *
	 * std::find_end
	 * Searches the range [first1,last1) for the last occurrence of the sequence defined by
	 * [first2,last2), and returns an iterator to its first element, or last1 if no occurrences
	 * are found.
	 *
	 * std::search_n
	 * Searches the range [first,last) for a sequence of count elements, each comparing equal
	 * to a value (or for which pred returns true).
	 *
	 * operator == or pred can be used for comparison for all the above algorithms
	 *
	 * clearly input iterators will not suffice.
	 *
	 */
	std::vector<int> subseq1{4,5,9,9};
	std::vector<int> subseq2{4,5,3};
	auto it3 = std::search(myvec.cbegin(),myvec.cend(),subseq1.cbegin(),subseq1.cend());
	//auto it3 = std::find_end(myvec.cbegin(),myvec.cend(),subseq1.cbegin(),subseq1.cend());
	//auto it3 = std::search_n(myvec.cbegin(),myvec.cend(),2,9);
	if(it3!=myvec.cend())
		std::cout<<"found sequence in vector at position "<<it3-myvec.cbegin()<<"\n";
	else
		std::cout<<"not found sequence in vector!\n";
	std::cout<<"**************************************\n";




	/*
	 * std::find_first_of
	 * Returns an iterator to the first element in the range [first1,last1) that matches any of the
	 * elements in [first2,last2). If no such element is found, the function returns last1.
	 *
	 * clearly input iterators will suffice for range [first1,last1) but not for [first2,last2).
	 */
	std::vector<int> subseq3{13,11};
	auto it4 = std::find_first_of(myvec.cbegin(),myvec.cend(),subseq3.cbegin(),subseq3.cend());
	if(it4!=myvec.cend())
		std::cout<<"match at position "<<it4-myvec.cbegin()<<"\n";
	else
		std::cout<<"no match!\n";
	std::cout<<"**************************************\n";




	/*
	 * std::adjacent_find
	 * Searches the range [first,last) for the first occurrence of two consecutive elements that
	 * match, and returns an iterator to the first of these two elements, or last if no such pair
	 * is found.
	 *
	 * why input iterators will not suffice? Imagine as if you were reading data from disk!
	 */
	auto it5 = std::adjacent_find(myvec.cbegin(),myvec.cend());
	if(it5!=myvec.cend())
		std::cout<<"adjacent match at position "<<it5-myvec.cbegin()<<"\n";
	else
		std::cout<<"no adjacent match!\n";
	std::cout<<"**************************************\n";




	/*
	 * std::count (similarly std::count_if accepts a pred)
	 * Returns the number of elements in the range [first,last) that compare equal to val.
	 *
	 * clearly input iterators will suffice.
	 */
	auto count = std::count(myvec.cbegin(),myvec.cend(),9);
	std::cout<<"count =  "<<count<<"\n";
	std::cout<<"**************************************\n";




	/*
	 * std::mismatch
	 * Compares the elements in the range [first1,last1) with those in the range beginning at
	 * first2, and returns the first element of both sequences that does not match.
	 *
	 * The elements are compared using operator== (or pred). The function returns a pair of
	 * iterators to the first element in each range that does not match.
	 *
	 * clearly input iterators will suffice.
	 */
	std::vector<int> subseq4{10,1,13,5,11};
	auto mypair = std::mismatch(myvec.cbegin(),myvec.cend(),subseq4.cbegin());
	std::cout<<"First mismatch of elements "<<*(mypair.first)<<" "<<*(mypair.second)<<"\n";
	++mypair.first; ++mypair.second;
	auto mypair2 = std::mismatch(mypair.first,myvec.cend(),mypair.second);
	std::cout<<"Second mismatch of elements "<<*(mypair2.first)<<" "<<*(mypair2.second)<<"\n";
	std::cout<<"**************************************\n";




	/*
	 * std::equal
	 * Compares the elements in the range [first1,last1) with those in the range beginning at
	 * first2, and returns true if all of the elements in both ranges match.
	 *
	 * The elements are compared using operator== (or pred)
	 *
	 * clearly input iterators will suffice.
	 */
	std::vector<int> mycopy(myvec.cbegin(),myvec.cend());
	bool flag = std::equal(myvec.cbegin(),myvec.cend(),mycopy.cbegin());
	if(flag)
		std::cout<<"All elements in range are equal\n";
	else
		std::cout<<"All elements in range are not equal\n";
	std::cout<<"**************************************\n";

	return 0;
}
