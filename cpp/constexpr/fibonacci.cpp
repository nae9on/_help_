/*
 * fibonacci.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: akadar
 */

#include <iostream>
#include <chrono>

using my_int = unsigned long long int;

#define gettime std::chrono::system_clock::now // is there a better way ?
#define dt std::chrono::duration<double> // is there a better way ?

// C++11's constexpr cannot have more than 1 return statement.
// There are more restrictions as mentioned here:
// https://stackoverflow.com/questions/45097171/the-body-of-constexpr-function-not-a-return-statement
// Some of the restrictions were listed in C++14.
constexpr my_int fib(my_int N){
	return N==0 ? 0 : (N==1 ? 1 : fib(N-1)+fib(N-2));
}

int fibonacci(){

	const int arg1 = 40;

	auto t1 = gettime();
	constexpr my_int x1 = fib(arg1); // fibonacci evaluated at compile-time
	std::cout<<"x1 = "<<x1<<"\n";
	auto t2 = gettime();

	auto t3 = gettime();
	int arg2 = arg1;
	my_int x2 = fib(arg2); // fibonacci evaluated at run-time
	std::cout<<"x2 = "<<x2<<"\n";
	auto t4 = gettime();

	std::cout << "elapsed time fib (compile-time evaluation): " << dt(t2-t1).count() << "s\n";
	std::cout << "elapsed time fib (run-time evaluation): " << dt(t4-t3).count() << "s\n";

	return 0;
}
