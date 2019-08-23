/*
 * fib1onacci.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: akadar
 */

#include <iostream>
#include <chrono>

using my_int = unsigned long long int;

#define gettime std::chrono::system_clock::now // is there a better way ?
#define dt std::chrono::duration<double> // is there a better way ?

/*
 * // Fibonacci version 1 using constexpr function.
 * C++11's constexpr function cannot have more than 1 return statement.
 * There are more restrictions as mentioned here:
 * https://stackoverflow.com/questions/45097171/the-body-of-constexpr-function-not-a-return-statement
 * Some of the restrictions were listed in C++14.
 *
 */
constexpr my_int fib1(my_int N){
	return N==0 ? 0 : (N==1 ? 1 : fib1(N-1)+fib1(N-2));
}

// Fibonacci version 2 using class template with constexpr
template<my_int N> struct fib2{
	const static my_int value = fib2<N-1>::value + fib2<N-2>::value;
};

template<> struct fib2<1>{
	const static my_int value = 1;
};

template<> struct fib2<0>{
	const static my_int value = 0;
};

int main(){

	const int arg1 = 40;

	auto t1 = gettime();
	constexpr my_int x1 = fib1(arg1); // fib1onacci evaluated at compile-time
	std::cout<<"x1 = "<<x1<<"\n";
	auto t2 = gettime();

	auto t3 = gettime();
	int arg2 = arg1;
	my_int x2 = fib1(arg2); // fib1onacci evaluated at run-time
	std::cout<<"x2 = "<<x2<<"\n";
	auto t4 = gettime();

	auto t5 = gettime();
	my_int x3 = fib2<40>::value; // fibonacci evaluated at compile-time
	std::cout<<"x3 = "<<x3<<"\n";
	auto t6 = gettime();

	std::cout << "elapsed time fib1 (compile-time evaluation): " << dt(t2-t1).count() << "s\n";
	std::cout << "elapsed time fib1 (run-time evaluation): " << dt(t4-t3).count() << "s\n";
	std::cout << "elapsed time fib2 (compile-time evaluation): " << dt(t6-t5).count() << "s\n";

	return 0;
}
