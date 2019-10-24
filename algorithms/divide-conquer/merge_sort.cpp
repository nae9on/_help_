/*
 * merge_sort.cpp
 *
 *  Created on: Oct 24, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

namespace myalgo{

template<typename T>
void merge_sort(T begin, T end){
	size_t len = end-begin;
	if(len<2){
		//std::sort(begin,end);
	}
	else{
		auto middle = begin+len/2;
		merge_sort<T>(begin, middle);
		merge_sort<T>(middle, end);
		std::inplace_merge(begin,middle,end);
	}
}
}

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

int merge_sort(){

	size_t len{1000000};

	std::vector<int> vec1(len,0), vec2(len,0);

	std::iota(vec1.begin(),vec1.end(),0);

	std::random_shuffle(vec1.begin(),vec1.end());

	std::copy(vec1.cbegin(), vec1.cend(), vec2.begin());

	// sort vec1 using std::sort
	auto t1 = clk::now();
	std::sort(vec1.begin(),vec1.end());
	auto t2 = clk::now();

	// sort vec2 using myalgo::merge_sort
	auto t3 = clk::now();
	myalgo::merge_sort(vec2.begin(),vec2.end());
	auto t4 = clk::now();

	auto pairIT = std::mismatch(vec1.cbegin(),vec1.cend(),vec2.cbegin());
	if(pairIT.first==vec1.cend() && pairIT.second==vec2.cend()){
		std::cout<<"Sorting is ok\n";
	}else{
		std::cout<<"Sorting is not ok\n";
	}

	std::cout<<"std::sort time = "<<dt(t2-t1).count()<<"\n";
	std::cout<<"myalgo::merge_sort time = "<<dt(t4-t3).count()<<"\n";

	//std::cout<<"\n";
	//for(const auto& elem : vec1) std::cout<<elem<<" ";
	//std::cout<<"\n";
	//for(const auto& elem : vec2) std::cout<<elem<<" ";
	return 0;
}
