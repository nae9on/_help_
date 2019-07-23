/*
 * arithmetic.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: akadar
 */

// Reference
// http://www.parashift.com/c++-faq-lite/operator-overloading.html

#include <iostream>

template<typename t> class complex{
public:
	complex() = default;
	complex(t r_, t c_): r{r_}, c{c_} {}
	t getr() const {return r;}
	t getc()const {return c;}

	// Tip
	// Operators with equality (+=, -=, *= etc) are usually member functions.
	// "normal" binary operators (+, -, * etc) are usually non-member friends.
	// This has to do with interface: if operator* was member, then A*5 would
	// be legal, but not 5*A.

    // The overload returns an l-value and therefore & can be used in the
	// return type
	complex<t>& operator+=(const complex<t>& c1) {
		std::cout<<"Operator += called for ("<<r<<"+"<<c<<"i) and ("<<c1.getr()<<"+"<<c1.getc()<<"i)\n";
		r += c1.getr();
		c += c1.getc();
		return *this;
	}

	// Note that the overload returns an r-value and therefore & is not used
	// in the return type.
	friend complex<t> operator+(const complex<t>& c1, const complex<t>& c2) {
		std::cout<<"Operator + called for ("<<c1.getr()<<"+"<<c1.getc()<<"i) and ("<<c2.getr()<<"+"<<c2.getc()<<"i)\n";
		return complex<t>(c1.getr()+c2.getr(),c1.getc()+c2.getc());
	}

	void print() const {
		std::cout<<"This = "<<this->getr()<<"+"<<this->getc()<<"i\n";
	}

private:
	t r{0}, c{0};
};

int main_arithmetic(){
	complex<double> c1(1.0,2.0), c2(3.0,4.0), c3(5.0,6.0);
	complex<double> c4 = c1 + c2 + c3;
	c4 += complex<double>(100.0,100.0);
	std::cout << c4.getr() << "+" << c4.getc() << "i\n";
	return 0;
}
