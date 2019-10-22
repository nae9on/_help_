/*
 * lambda.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
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
#include <cmath>
#include <numeric>
#include <limits>

// Defining a comparator class
template <typename T>
class comparator {
	const T value;
public:
	comparator(const T& v) : value{v} {}
	bool operator()(const T& v){return v>value;}
};

// Defining sum algorithm, which accepts a container, an initial value, and a predicate argument
template <typename E, typename S, typename P> S sum(const E& e, S s, P pred) {
	for (const auto& t:e) {
		if(pred(t))
		s+=t;
	}
	return s;
}

int lambda()
{
	std::cout << "In lambda\n";
	std::vector<double> e = {1.0,2.0,3.0,4.0001,9.0,625};
	double s {0.0};
	double lowerLimit {0.0};
	double upperLimit {5.0};

	// Function objects used as predicate arguments to algorithms
	comparator<float> comp(0.0);
	// Note automatic type deduction of the template arguments of sum
	std::cout<<"Sum of +ve numbers using functor (form 1) = "
			<<sum(e,s,comparator<double>(0.0))<<std::endl;
	std::cout<<"Sum of +ve numbers using functor (form 2) = "
			<<sum(e,s,comp)<<std::endl;

	/*
	 * Lambdas are syntactic sugar for anonymous functors. They allow to implicitly generate a
	 * function object using a more convenient and terse expression.
	 *
	 * For lambdas, the explicit use of the trailing-return-type can be omitted if it can be
	 * easily deduced by the compiler.
	 */
	std::cout<<"Sum of +ve numbers using Lambda expression = "
			<<sum(e,s,[](double a)->bool{return a>0;})<<std::endl;

	/*
	 * Syntax of capture list:
	 * Example capture total by reference and the external variable factor by value
	 * [&total, factor]
	 * [factor, &total]
	 * [&, factor]
	 * [factor, &]
	 * [=, &total]
	 * [&total, =]
	 */
	// Calculate sum of all perfect squares using Lambda expression
	double sumPerfectSquares = sum(e,s,[&lowerLimit,upperLimit](double a)->bool{
		double sqrta = std::round(std::sqrt(a));
		bool isSquare = 0;
		if (a>lowerLimit && a<upperLimit) {
			if(std::fabs(sqrta*sqrta-a)<std::numeric_limits<double>::epsilon()) {
				isSquare = 1;
			}
		}
		return isSquare;
	});
	std::cout<<"Sum of perfect squares (less than partition) using Lambda expression = "
			<<sumPerfectSquares<<std::endl;

	return 0;
}
