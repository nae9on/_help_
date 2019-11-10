/*
 * return_type_deduction_lambda.cpp
 *
 *  Created on: 07 Nov 2019
 *      Author: ahkad
 *
 * Reference
 * Item 31, Effective Modern C++, Scott Meyers
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

template<typename IT>

// C++11 supports trailing-return-type (auto is not playing any role here)
//auto getMedian(IT begin, IT end)->int{ // C++11, not very useful as int is hard-coded (form 1)
//auto getMedian(IT begin, IT end)->decltype(*begin){ // C++11, decltype type-deduction rules applied (form 2)

// trailing-return type can be omitted in C++14
//auto getMedian(IT begin, IT end){ // C++14, auto type-deduction rules applied (form 3)
decltype(auto) getMedian(IT begin, IT end){ // C++14, decltype type-deduction rules applied (form 4 same as form 2)

	std::sort(begin,end);

	return *(begin+static_cast<size_t>(end-begin)/2);

}

int return_type_deduction_lambda(){

	std::vector<int> v{3,1,5,2,9,4,6};

	using IT = std::vector<int>::iterator;

	//auto lmb = [](IT begin, IT end)->int { // C++11, similar to form 1 above
	//auto lmb = [](IT begin, IT end)->decltype(*begin) { // C++11, similar to form 2 above
	//auto lmb = [](IT begin, IT end) { // C++11, return-type deduced by compiler for simple cases
	//auto lmb = [](auto begin, auto end) { // C++14, similar to form 3 above
	auto lmb = [](auto begin, auto end)->decltype(auto) { // C++14, similar to form 4 above

		std::sort(begin,end);

		return *(begin+static_cast<size_t>(end-begin)/2);

	};

	void f(IT); // to disable warning

	std::cout<<lmb(v.begin(),v.end())<<"\n";

	std::cout<<getMedian(v.begin(),v.end())<<"\n";

	return 0;
}
