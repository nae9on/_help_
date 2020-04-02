/*
 * overload_io.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: akadar
 */

#include <iostream>
#include <ostream>

class pixel{
public:
	pixel() = default;
	pixel(short r_, short g_, short b_): r{r_}, g{g_}, b{b_}{}
	short getr() const{ return r;}
	short getg() const { return g;}
	short getb() const{ return b;}

	friend std::ostream& operator<<(std::ostream& os, const pixel& p) {
		os<<"["<<p.getr()<<","<<p.getg()<<","<<p.getb()<<"]\n";
		return os;
	}
private:
	short r{0}, g{0}, b{0};
};

// Note that the operator<< can also be overloaded outside the class.
// Advantages/disadvantages?

int overload_io(){
	pixel p1, p2(1,2,3);
	std::cout<<p1<<p2;
	return 0;
}
