/*
 * arithmetic.cpp
 *
 *  Created on: Jul 17, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://docs.microsoft.com/en-us/cpp/cpp/operator-overloading?view=vs-2019
 * [2] https://en.cppreference.com/w/cpp/language/operators
 * [3] http://www.parashift.com/c++-faq-lite/operator-overloading.html
 * [4] https://docs.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-
 * overloading-cpp?view=vs-2019
 * [5] https://isocpp.org/wiki/faq/operator-overloading#creating-new-opers
 */

#include <iostream>
#include <type_traits>
#include <cassert>

template<typename t> class complex{
public:
	complex() = default;
	complex(t r_, t c_): r{r_}, c{c_} {}

	/*
	 * Notes:
	 *
	 * 1. One can redefine the function of most built-in operators globally or on a class-by-class basis.
	 * For user-defined types, they can be implemented as both member functions or non-member functions.
	 *
	 * 2. Non-member functions are overloaded outside the class (in file scope) and they can be
	 * declared friend of the class if needed.
	 *
	 * 3. Unary operators ++, --, +, -, &(address-of), *(dereference), !(logical NOT),
	 * ~(1's complement) are usually member functions.
	 *
	 * 4. Binary operators with equality (+=, -=, *= etc) are usually member functions.
	 *
	 * 5. Some binary operators (+, -, * etc) are usually non-member functions or friend functions.
	 * This has to do with interface: if operator+ was a class member, then A+5 would be legal,
	 * but not 5+A.
	 */

	// Overloaded unary prefix-increment [4]
	complex<t>& operator++(){
		std::cout<<"Operator prefix-increment called for "<<*this<<"\n";
		++r;
		++c;
		return *this; // returns an l-value, hence & can be used in the return type
	}

	// Overloaded unary postfix-increment [4]
	complex<t> operator++(int){
		std::cout<<"Operator postfix-increment called for "<<*this<<"\n";
		complex<t> temp(r,c);
		++r; ++c; // or do this instead ++*this;
		return temp; // returns an r-value, hence & is not used in the return type
	}

    // Overloaded binary +=
	complex<t>& operator+=(const complex<t>& x){
		std::cout<<"Operator += called for "<<*this<< " and "<<x<<"\n";
		r += x.r;
		c += x.c;
		return *this;
	}

	// Overloaded unary -
	complex<t>& operator-(){
		std::cout<<"Operator - called for "<<*this<<"\n";
		r = -r;
		c = -c;
		return *this;
	}

	// Can't make friend's, something wrong down here?
	//friend complex<t> operator+(const complex<t>&, const complex<t>&);
	//friend complex<t> operator+(const complex<t>&, v);
	//friend complex<t> operator+(v, const complex<t>&);
	//friend std::ostream& operator << (std::ostream&, const complex<t>&);

	t r{0}, c{0}; // made public for illustration purpose only
};

// Overloaded binary complex + complex
template<typename t>
complex<t> operator+(const complex<t>& x1, const complex<t>& x2) {
	std::cout<<"Operator + called for "<<x1<< " and "<<x2<<"\n";
	return complex<t>(x1.r+x2.r,x1.c+x2.c); // returns an r-value
}

// Overloaded binary complex + arithmetic type
template<typename t, typename v>
complex<t> operator+(const complex<t>& x1, v x2) {
	static_assert(std::is_arithmetic<v>::value,"Only integral types allowed");
	std::cout<<"Operator + called for "<<x1<< " and "<<x2<<"\n";
	return complex<t>(x1.r+x2,x1.c+0);
}

// Overloaded binary arithmetic type + complex
template<typename t, typename v>
complex<t> operator+(v x1, const complex<t>& x2) {
	static_assert(std::is_arithmetic<v>::value,"Only integral types allowed");
	std::cout<<"Operator + called for "<<x1<< " and "<<x2<<"\n";
	return complex<t>(x1+x2.r,x2.c);
}

// Overloaded binary << (left shift operator)
template<typename t>
std::ostream& operator<<(std::ostream& out, const complex<t>& c){
	if(c.c>0)
		return out << "("<< c.r << "+" << c.c << "i)";
	else
		return out << "("<< c.r << "-" << -c.c << "i)";
}

int arithmetic(){
	complex<double> x1(1.0,2.0), x2(3.0,4.0), x3(5.0,6.0);
	complex<double> x4 = 1 + x1 + x2 + x3 + 2;
	x4 += complex<double>(100.0,100.0);
	x4.operator-(); // same as -x4, which is an implicit call by the compiler
	std::cout<<x4.operator++()<<"\n"; // same as ++x4
	std::cout<<x4.operator++(3)<<"\n"; // same as x4++, with argument 3 ignored
	std::cout<<x4<<"\n";
	return 0;
}
