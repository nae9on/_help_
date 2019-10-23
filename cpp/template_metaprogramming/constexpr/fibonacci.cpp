/*
 * fibonacci.cpp
 *
 *  Created on: Aug 20, 2019
 *      Author: akadar
 */

#include <iostream>
#include <chrono>

using my_int = unsigned long long int;

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

/*
 * // Fibonacci version 1 using constexpr function.
 * C++11's constexpr function cannot have more than 1 return statement.
 * There are more restrictions as mentioned here:
 * https://stackoverflow.com/questions/45097171/the-body-of-constexpr-function-not-a-return-statement
 * Some of the restrictions were removed in C++14.
 *
 */
constexpr my_int fib1(my_int N){
	return N==0 ? 0 : (N==1 ? 1 : fib1(N-1)+fib1(N-2));
}

// Fibonacci version 2 using class template with constexpr
template<my_int N> struct fib2{
public:
	constexpr fib2(){};
	constexpr static my_int get_value(){
		return value;
	}
private:
	constexpr static my_int value = fib2<N-1>::get_value() + fib2<N-2>::get_value();
};

template<> struct fib2<1>{
public:
	constexpr fib2(){};
	constexpr static my_int get_value(){
		return value;
	}
private:
	constexpr static my_int value = 1;
};

template<> struct fib2<0>{
public:
	constexpr fib2(){};
	constexpr static my_int get_value(){
		return value;
	}
private:
	constexpr static my_int value = 0;
};

int fibonacci(){

	const int arg1 = 40;

	auto t1 = clk::now();
	constexpr my_int x1 = fib1(arg1); // fib1onacci evaluated at compile-time
	std::cout<<"x1 = "<<x1<<"\n";
	auto t2 = clk::now();

	auto t3 = clk::now();
	int arg2 = arg1;
	my_int x2 = fib1(arg2); // fib1onacci evaluated at run-time
	std::cout<<"x2 = "<<x2<<"\n";
	auto t4 = clk::now();

	auto t5 = clk::now();
	constexpr fib2<40> fib_obj;
	constexpr my_int x3 = fib_obj.get_value(); // fibonacci evaluated at compile-time
	std::cout<<"x3 = "<<x3<<"\n";
	auto t6 = clk::now();

	std::cout<<"fib2<40> is a literal-type is "<<std::is_literal_type<fib2<40>>::value<<"\n";

	std::cout << "elapsed time fib1 (compile-time evaluation): " << dt(t2-t1).count() << "s\n";
	std::cout << "elapsed time fib1 (run-time evaluation): " << dt(t4-t3).count() << "s\n";
	std::cout << "elapsed time fib2 (compile-time evaluation): " << dt(t6-t5).count() << "s\n";

	return 0;
}
