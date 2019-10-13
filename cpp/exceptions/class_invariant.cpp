/*
 * class_invariant.cpp
 *
 *  Created on: Jul 11, 2019
 *      Author: akadar
 *
 * Invariant - a statement that is assumed to be true for a class.
 * It is the job of a constructor to establish the invariant of a class (so that member functions
 * can rely on it) and for the member functions to make sure that the invariant holds when they
 * exit - Pg 37, Bjarne Stroustrup in "A Tour of C++".
 */

#include <iostream>
#include <stdexcept> // std::invalid_argument, std::out_of_range
#include <type_traits> // std::is_same

using uchar = unsigned char;

template<typename t> class pixel {
public:
	pixel() = default;
	pixel(double, double, double);
	void out_rgb() const{
		std::cout<<"("<<r<<","<<g<<","<<b<<")"<<"\n";
	}
private:
	const t W{255}, B{0};
	t r{W}, g{W}, b{W}; // white color by default
};

template<typename t> pixel<t>::pixel(double r_, double g_, double b_) {
	try
	{
	try {

		// Exceptions occur at run-time.
		// However, if errors can be checked at compile-time it is even better.

		// check at compile-time if template argument is not uchar
		// note the argument to static_assert must evaluate to a constexpr
		constexpr bool checkInt = std::is_same<t, uchar>::value;
		static_assert(checkInt,"template argument is not uchar");

		// Check at run-time if template argument is not uchar - not useful
		if(!std::is_same<t, uchar>::value)
			throw std::invalid_argument("template argument is not uchar");

		// Check if r,g,b are integers
		if (r_!=static_cast<int>(r_)) throw std::invalid_argument("r value not an int");
		if (g_!=static_cast<int>(g_)) throw std::invalid_argument("g value not an int");
		if (b_!=static_cast<int>(b_)) throw std::invalid_argument("b value not an int");

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
	r = static_cast<uchar>(r_);
	g = static_cast<uchar>(g_);
	b = static_cast<uchar>(b_);
}

int class_invariant() {
	pixel<uchar>(1,6,5);
	pixel<uchar>(1,3,256);
	return 0;
}
