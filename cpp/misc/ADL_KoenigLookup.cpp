/*
 * ADL_KoenigLookup.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: akadar
 *
 * Koenig Lookup, or Argument Dependent Lookup, describes how unqualified names are
 * looked up by the compiler in C++. This example illustrates this.
 *
 * References:
 * https://stackoverflow.com/questions/25286544/how-does-the-standard-library-implement-stdswap
 * https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup
 */

#include <iostream>
#include <vector>

namespace my_ns
{
class X{
public:
	X(){
		n = 0;
	}
	X(size_t n_){
		n = n_;
		data.resize(n_);
	}
	X(const X& x){
		n = x.n;
		data = x.data;
		std::cout<<"copy-const\n";
	}
	X& operator=(const X& x){
		n = x.n;
		data = x.data;
		std::cout<<"copy-assign\n";
		return *this;
	}
	X(X&& x){
		n = std::move(x.n);
		data = std::move(x.data);
		std::cout<<"move-const\n";
	}
	X& operator=(X&& x){
		n = std::move(x.n);
		data = std::move(x.data);
		std::cout<<"move-assign\n";
		return *this;
	}
private:
	size_t n;
	std::vector<double> data;
};

void swap(X& x1, X& x2){
	X temp = std::move(x1);
	x1 = std::move(x2);
	x2 = std::move(temp);
	std::cout<<"My-swap\n";
}
}

using std::swap;

int ADL_KoenigLookup(){

	my_ns::X x1(10);
	my_ns::X x2(x1);
	my_ns::X x3; x3 = x2;
	my_ns::X x4(my_ns::X(20)); // disable copy-elision (using -fno-elide-constructors) to see the MOVE magic
	my_ns::X x5;
	x5 = my_ns::X(30);

	std::cout<<"\n\n";

	swap(x1,x5); // Resorts to my_ns::swap (due to ADL) even when std::swap is qualified

	std::cout<<"\n\n";

	std::swap(x1,x5); // Resorts to std::swap of course

	return 0;
}
