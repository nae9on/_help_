/*
 * basic_lambda.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 *
 * Lambdas are syntactic sugar for anonymous functors. They allow to implicitly generate a
 * function object using a more convenient and terse expression.
 *
 * Example to demonstrate use of anonymous function objects (or lambdas) as parameters to
 * algorithms.
 *
 * References:
 * https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=vs-2019
 *
 */

#include <iostream>
#include <vector>
#include <numeric> // accumulate

int basic_lambda()
{

	/*
	 * Syntax of capture list:
	 * Example capture lower by reference and the external variable upper by value
	 * [&lower, upper]
	 * [upper, &lower]
	 * [&, upper]
	 * [upper, &]
	 * [=, &lower]
	 * [&lower, =]
	 *
	 * 	 *
	 * Note:
	 * 1. The explicit use of the trailing-return-type can be omitted if it can be easily deduced
	 * by the compiler (if it cannot be deduced by the compiler then it can be explicitly mentioned
	 * or decltype can be used).
	 * 2. 'auto' in lambda parameter declaration only available with -std=c++14
	 * 3. type deduction in lambda parameter declaration is governed by template type deduction
	 * and not auto type deduction (Item 2, Effective Modern C++).
	 */

	std::vector<int> vec {1,3,4,6,20};

	int lower{0}, upper{10};

	std::cout<<"Sum of all evens in the vector using std::accumulate = "
			<<std::accumulate(vec.cbegin(),vec.cend(),0,
					//[lower,upper](const int& a, const int& b)->int // c++11
					//[lower,upper](const int& a, const int& b)      // c++11
					[lower,upper](const auto& a, const auto& b)      // c++14
					{
						if(b%2==0 && b>=lower && b<=upper)
							return (a+b);
						else {
							return a;
						}
					})<<std::endl;

	return 0;
}
