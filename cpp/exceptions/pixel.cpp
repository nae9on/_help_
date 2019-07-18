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

class pixel {
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
	const short W = 255, B = 0;
	short r{W}, g{W}, b{W}; // white color by default
};

pixel::pixel(double r_, double g_, double b_) {
	try
	{
	try {
		// Check if r,g,b is not a number Ex pixel('a','b','c') ?

		// Check if r,g,b are integers
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
		std::cout<<"Wrong [r g b] value entered\n";
		std::terminate(); // terminate called since this error is non-recoverable
	}
	r = static_cast<short>(r_);
	g = static_cast<short>(g_);
	b = static_cast<short>(b_);
}

int main() {
	pixel(1,6,7.5);
	pixel(1,2,3);
	return 0;
}
