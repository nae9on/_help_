/*
 * fibonacci.cpp
 *
 *  Created on: Jul 28, 2019
 *      Author: akadar
 *
 *  Template recursion is a useful optimization technique that can be used to compute
 *  factorials, fibonacci numbers etc . The recursion is evaluated at compile time thus
 *  resulting in no run time overhead.
 */

#include<iostream>
#include<chrono>

using my_int = unsigned long long int;

#define gettime std::chrono::system_clock::now // is there a better way ?
#define dt std::chrono::duration<double> // is there a better way ?

// Fibonacci version 1 using function template
template<my_int itr> my_int fib1(){
		return fib1<itr-1>()+fib1<itr-2>();
}

template<> my_int fib1<1>(){
		return 1;
}

template<> my_int fib1<0>(){
		return 0;
}

// Fibonacci version 2 using class template
template<my_int N> struct fib2{
    enum : my_int
    {
        value = fib2<N-1>::value + fib2<N-2>::value
    };
};

template<> struct fib2<1>{
    enum : my_int
    {
        value = 1
    };
};

template<> struct fib2<0>{
    enum : my_int
    {
        value = 0
    };
};

// Fibonacci version 3 using class template
template<my_int N> struct fib3{
	const static my_int value = fib3<N-1>::value + fib3<N-2>::value;
};

template<> struct fib3<1>{
	const static my_int value = 1;
};

template<> struct fib3<0>{
	const static my_int value = 0;
};

// Fibonacci version 4 without using templates
my_int fib_noTemp(my_int N){
	if (N==0)
		return 0;
	else if(N==1)
		return 1;
	else
		return fib_noTemp(N-1)+fib_noTemp(N-2);
}

int main_fibonacci(){
	std::cout<<"In main\n";

	/*
	 * Note that Fibonacci version 1 is extremely slow for large input parameter (>50)
	 * because although all the instances fib1<N>, fib1<N-1>, ... fib<1>, fib<0> etc
	 * are instantiated at compile time in almost no time, there recursive call at run-time
	 * is extremely slow due to pass-by-copy of the return value.
	 */

	auto t1 = gettime();
	std::cout<<"\nfib1 = "<<fib1<40>()<<"\n";

	auto t2 = gettime();
	std::cout<<"\nfib2 = "<<fib2<40>::value<<"\n";

	auto t3 = gettime();
	std::cout<<"\nfib3 = "<<fib3<40>::value<<"\n";

	auto t4 = gettime();
	std::cout<<"\nfib_noTemp = "<<fib_noTemp(40)<<"\n";

	auto end = gettime();

	std::cout << "\nelapsed time fib1: " << dt(t2-t1).count() << "s\n";
	std::cout << "elapsed time fib2: " << dt(t3-t2).count() << "s\n";
	std::cout << "elapsed time fib3: " << dt(t4-t3).count() << "s\n";
	std::cout << "elapsed time fib_noTemp: " << dt(end-t4).count() << "s\n";
	return 0;
}
