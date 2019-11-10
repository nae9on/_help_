/*
 * basic_functor.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 *
 *  Example to demonstrate use of function objects as parameters to algorithms.
 *  A function object (sometimes referred to as a policy object) carries data + efficiency.
 *
 */

#include <iostream>
#include <vector>
#include <numeric> // accumulate

// Defining a predicate class
class testEven{
public:
	testEven(){
		lower = 0;
		upper = 10;
	}
	// unary op for myAccumulate
	// making the function call op inline allows compiler optimization
	// prefer functors instead of plain functions as algorithm parameters (Item 46, Effective STL)
	inline bool operator()(const int& a) const{
		return (a%2==0 && a>=lower && a<=upper);
	}
	inline int operator()(const int& a, const int& b) const;
private:
	// state
	int lower;
	int upper;
};

// binary op for std::accumulate
int testEven::operator()(const int& a, const int& b) const{
	if(b%2==0 && b>=lower && b<=upper)
		return (a+b);
	else {
		return a;
	}
}

// my accumulator which accepts begin and end iterators,
// initial value and a unary function object as a predicate
template <typename T, typename S, typename Pred>
S myAccumulate(T _first, T _last, S _init, Pred _p){
	for (;_first != _last; ++_first) {
		if (_p(*_first)) // test predicate
			_init += *_first;
	}
	return _init;
}

int basic_functor()
{
	std::cout<<"In functor\n";

	// Defining a function object
	testEven pred;

	// Test function object
	std::cout<<"Test predicate "<<pred(2)<<"\n";
	std::cout<<"Test predicate "<<pred(3)<<"\n";

	// Use function object as a parameter to an algorithm
	std::vector<int> vec {1,3,4,6,20};
	// Note automatic type deduction of the template arguments of both accumulate functions
	std::cout<<"Sum of all evens in the vector using std::accumulate = "
			<<std::accumulate(vec.cbegin(),vec.cend(),0,pred)<<std::endl;
	std::cout<<"Sum of all evens in the vector using myAccumulate = "
			<<myAccumulate(vec.cbegin(),vec.cend(),0,pred);
	return 0;
}
