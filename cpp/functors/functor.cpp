/*
 * functor.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 *
 *  Example to demonstrate use of function objects as parameters to algorithms.
 *  A function object (sometimes referred to as policy object) carries data + efficiency.
 */

#include <iostream>
#include <vector>
#include <numeric> // accumulate
#include <cmath> // fabs, sqrt
#include <limits> // numeric_limits<double>::epsilon()

using DLIMITS = std::numeric_limits<double>;

// Defining a predicate class
// T1 type represents sum, T2 type represents container's value_type
template <typename T1, typename T2>
class testSquares{
private:
	const T2 zero;
public:
	testSquares(const T2& _zero): zero{_zero} {}

	// unary op for myAccumulate
	inline bool operator()(T2 a){
		if(a<zero)
			return false;
		else {
			double da = static_cast<double>(a);
			double sqrtb = std::round(std::sqrt(da));
			return (std::fabs(sqrtb*sqrtb-da)<DLIMITS::epsilon());
		}
	}
	inline T1 operator()(T1 a, T2 b);
};

// binary op for std::accumulate
template <typename T1, typename T2>
T1 testSquares<T1,T2>::operator()(T1 a, T2 b){
	if(b<zero)
		return a;
	else {
		double db = static_cast<double>(b);
		double sqrtb = std::round(std::sqrt(db));
		if(std::fabs(sqrtb*sqrtb-db)<DLIMITS::epsilon())
			return static_cast<T1>(a+b);
		else
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

int functor()
{
	std::cout<<"In functor\n";

	// Defining a function object
	testSquares<double,int> pred(0);

	// Test function object
	std::cout<<"Test predicate "<<pred(9)<<"\n";
	std::cout<<"Test predicate "<<pred(0.0,9)<<"\n";

	// Use function object as a parameter to an algorithm
	std::vector<int> vec {-1,0,1,2,4,8,16,32,100};
	// Note automatic type deduction of the template arguments of both accumulate functions
	std::cout<<"Sum of all squares in the vector using std::accumulate = "
			<<std::accumulate(vec.cbegin(),vec.cend(),0.0,pred)<<std::endl;
	std::cout<<"Sum of all squares in the vector using myAccumulate = "
			<<myAccumulate(vec.cbegin(),vec.cend(),0.0,pred);
	return 0;
}
