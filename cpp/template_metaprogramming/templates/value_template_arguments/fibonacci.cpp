/*
 * fibonacci.cpp
 *
 *  Created on: Jul 28, 2019
 *      Author: akadar
 *
 *  Template recursion is a useful optimization technique that can be used to compute
 *  factorials, fibonacci numbers etc. The recursion is evaluated at compile time thus
 *  resulting in no run time overhead.
 */

#include<iostream>
#include<chrono>
#include<cmath>

using clk = std::chrono::system_clock;
using dt = std::chrono::duration<double>;

using std::cout;

// Fibonacci version 1 using function template
template<size_t itr> size_t fib1(){
		return fib1<itr-1>()+fib1<itr-2>();
}

template<> size_t fib1<1>(){
		return 1;
}

template<> size_t fib1<0>(){
		return 0;
}

// Fibonacci version 2 using struct template and enum class (i.e. scoped enum)
template<size_t N> struct fib2{
    enum class X: size_t{value = static_cast<size_t>(fib2<N-1>::X::value) +
    							 static_cast<size_t>(fib2<N-2>::X::value)};
};

template<> struct fib2<1>{
    enum class X: size_t{value = 1};
};

template<> struct fib2<0>{
    enum class X: size_t{value = 0};
};

// Fibonacci version 3 using struct template and static const
template<size_t N> struct fib3{
	static const size_t value = fib3<N-1>::value + fib3<N-2>::value;
};

template<> struct fib3<1>{
	static const size_t value = 1;
};

template<> struct fib3<0>{
	static const size_t value = 0;
};

// Fibonacci version 4 without using templates
size_t fib_noTemp(const size_t& N){
	if (N==0)
		return 0;
	else if(N==1)
		return 1;
	else
		return fib_noTemp(N-1)+fib_noTemp(N-2);
}

int main_fibonacci(){

	cout<<"Size of size_t = "<<sizeof(size_t)<<"\n";
	cout<<"Max value that size_t can accommodate = "<<std::pow(2,8*sizeof(size_t))<<"\n";
	cout<<"This limits the max number for which fibonacci can \nbe calculated correctly to 93\n";

	const size_t alpha{40};
	// https://www.omnicalculator.com/math/fibonacci

	/*
	 * Note that Fibonacci version 1 is extremely slow for large input parameter (>50)
	 * because although all the instances fib1<N>, fib1<N-1>, ... fib<1>, fib<0> etc
	 * are instantiated at compile time in almost no time, their recursive call at run-time
	 * is extremely slow due to pass-by-copy of the return value.
	 */

	auto t1 = clk::now();
	cout<<"\nfib1 = "<<fib1<alpha>()<<"\n";

	auto t2 = clk::now();
	cout<<"\nfib2 = "<<static_cast<size_t>(fib2<alpha>::X::value)<<"\n";

	auto t3 = clk::now();
	cout<<"\nfib3 = "<<fib3<alpha>::value<<"\n";

	auto t4 = clk::now();
	cout<<"\nfib_noTemp = "<<fib_noTemp(alpha)<<"\n";

	auto end = clk::now();

	cout << "\nelapsed time fib1: " << dt(t2-t1).count() << "s\n";
	cout << "elapsed time fib2: " << dt(t3-t2).count() << "s\n";
	cout << "elapsed time fib3: " << dt(t4-t3).count() << "s\n";
	cout << "elapsed time fib_noTemp: " << dt(end-t4).count() << "s\n";
	return 0;
}
