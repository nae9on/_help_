/*
 * pixel.cpp
 *
 *  Created on: Jul 11, 2019
 *      Author: akadar
 */

#include<iostream>
#include<vector>
#include<stdexcept>
#include<cmath>

#include <type_traits> // defines std::is_same

template <typename t> class pixel {
public:
	pixel() = default;
	pixel(double, double, double);
	void out_rgb() const{
		std::cout<<"("<<r<<","<<g<<","<<b<<")"<<"\n";
	}
	bool is_integer(double k)
	{
	  return std::floor(k) == k;
	}
private:
	const t W = 255, B = 0;
	t r{W}, g{W}, b{W}; // white color by default
};

template <typename t>  pixel<t>::pixel(double r_, double g_, double b_) {
	try
	{
	try {

		// normally exceptions occur at run-time, however, if they can be checked
		// at compile-time it is even better.
		// check at compile-time if template argument is not int
		// note the argument to static_assert must evaluate to a constexpr
		constexpr bool checkInt = std::is_same<t, int>::value;
		static_assert(checkInt,"template argument is not int");

		// Check at run-time if template argument is not int - not useful
		if(!std::is_same<t, int>::value) throw std::invalid_argument("template argument is not int");

		// Check if r,g,b are not floats
		if(!is_integer(r_)) throw std::invalid_argument("r value is not an integer");
		if(!is_integer(g_)) throw std::invalid_argument("g value is not an integer");
		if(!is_integer(b_)) throw std::invalid_argument("b value is not an integer");

		// Check if r,g,b are in [0 255]
		if (r_<0 || r_>255)	throw std::out_of_range("r value not in [0 255]");
    	if (g_<0 || g_>255) throw std::out_of_range("g value not in [0 255]");
		if (b_<0 || b_>255)	throw std::out_of_range("b value not in [0 255]");
	}
	catch(const std::invalid_argument& e){
		std::cout<<e.what()<<"\n";
		throw; // original exception re-thrown
	}
	catch(const std::out_of_range& e){
		std::cout<<e.what()<<"\n";
		throw; // original exception re-thrown
	}
	}
	catch(const std::exception& e){ // Note that a base class handler is used
		std::terminate(); // terminate called since this error is non-recoverable
	}
	r = r_;
	g = g_;
	b = b_;
}

int main() {
	pixel<int>(1,6,500);
	pixel<int>(1,2,3);
	return 0;
}
