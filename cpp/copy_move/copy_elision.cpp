/*
 * copy_elision.cpp
 *
 *  Created on: Sep 18, 2019
 *      Author: akadar
*
 * copy elision refers to a compiler optimization technique that eliminates unnecessary
 * copying of objects. It can be disabled using flag -fno-elide-constructors
 *
 * References:
 * [1] https://en.wikipedia.org/wiki/Copy_elision
 * [2] https://en.cppreference.com/w/cpp/language/throw
 */

#include <iostream>

int n{0};

struct X{
	X(int d_):d{d_}{
		++n;
		std::cout<<"Ordinary constructor called\n";
	}
	X(const X& x){
		++n; //  if the copy constructor has side effects, copy elision can change program behavior
		d = x.d;
		std::cout<<"Copy constructor called\n";
	}
	X& operator=(const X& x){
		++n;
		d = x.d;
		std::cout<<"Copy assignment called\n";
		return *this;
	}
	X(X&& x){
		d = x.d;
		std::cout<<"Move constructor called\n";
	}
	X& operator=(X&& x){
		++n;
		d = std::move(x.d);
		std::cout<<"Move assignment called\n";
		return *this;
	}
	int d;
};

X returnX7(){
	return X(7);
}

int copy_elision(){

	// Abbreviations
	// copy-elid-yes - when copy-elision is enabled
	// move-yes - when move semantics is enabled.

	/*
	 * Important notes:
	 * In C++11, when both are enabled, copy-elision takes precedence over move-semantics
	 * and therefore move-semantics is not used but still the compiler complaints when
	 * move-constructor is deleted!
	 *
	 * In C++98, when copy-elision is disabled, copy-const is used otherwise not.
	 *
	 */

	X x1(7); // ord-const called.

	std::cout<<"\n";

	X x2(x1); // copy-const called.

	std::cout<<"\n";

	/*
	 * ord-const, move-const called when copy-elid-no and move-yes
	 * only ord-const called when copy-elid-yes and move-yes
	 * ord-const, copy-const called when copy-elid-no and move-no (only allowed with c++98)
	 */
	X x3(X(7));

	std::cout<<"\n";

    try{

    	/*
    	 * the exception object is considered to be an lvalue argument [2]
    	 * ord-const, move-const called when copy-elid-no and move-yes
    	 * only ord-const called when copy-elid-yes and move-yes
    	 * ord-const, copy-const called when copy-elid-no and move-no
    	 */
    	throw X(7);

	}catch(const X& x){

		std::cout<<"x.d="<<x.d<<"\n";

	}catch(...){

		std::cout<<"ellipsis catch\n";
	}

	std::cout<<"\n";

	/*
	 * Return Value Optimization (RVO) is a compiler optimization that involves eliminating
	 * the temporary object created to hold a function's return value.
	 *
	 * ord-const, move-const, move-const called when copy-elid-no and move-yes
	 * only ord-const called when copy-elid-yes and move-yes
	 * ord-const, copy-const, copy-const called when copy-elid-no and move-no
	 *
	 */
	X x4 = returnX7();

	(void) x4; // cast to void

	return 0;
}
