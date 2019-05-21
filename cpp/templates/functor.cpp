/*
 * functor.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <limits>

// Defining a predicate class
template <typename T>
class testSquares{
private:
	const T zero;
public:
	testSquares(const T& _zero): zero{_zero} {}
	inline bool operator()(T a){
		if(a<zero)
			return 0;
		else {
			double da = static_cast<double>(a);
			double sqrtb = std::round(std::sqrt(da));
			return (std::fabs(sqrtb*sqrtb-a)<std::numeric_limits<double>::epsilon());
		}
	}
	inline T operator()(T a, T b);
};

template <typename T>
T testSquares<T>::operator()(T a, T b){
	if(b<zero)
		return a;
	else {
		double db = static_cast<double>(b);
		double sqrtb = std::round(std::sqrt(db));
		if(std::fabs(sqrtb*sqrtb-b)<std::numeric_limits<double>::epsilon())
			return a+b;
		else
			return a;
	}
}

// Defining my accumulator which accepts begin and end iterators,
// initial value and a function object as a predicate
template <typename T, typename S, typename Pred>
S myAccumulate(T _first, T _last, S _init, Pred _p){
	for (; _first != _last; _first++) {
		if (_p(*_first)) // test predicate
			_init += *_first;
	}
	return _init;
}

int main_functor()
//int main()
{
	std::cout<<"In functor\n";

	// Defining a function object
	testSquares<double> pred(0);

	// Test function object
	std::cout<<"Test predicate "<<pred(8.9999999999999999)<<"\n";
	std::cout<<"Test predicate "<<pred(0,8.9999999999999999)<<"\n";

	// Use function object as a parameter to an algorithm
	std::vector<double> vec {-1,0,1,2,4,8,16,32,100,100.5,100.1};
	std::cout<<"Sum of all squares in the vector using std::accumulate = "
			<<std::accumulate(vec.cbegin(),vec.cend(),0.0,pred)<<std::endl;
	std::cout<<"Sum of all squares in the vector using myAccumulate = "
			<<myAccumulate(vec.cbegin(),vec.cend(),0.0,pred);
	return 0;
}
