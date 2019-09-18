/*
 * copy_elision.cpp
 *
 *  Created on: Sep 18, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://en.wikipedia.org/wiki/Copy_elision
 * [2] https://en.cppreference.com/w/cpp/language/throw
 */

#include <iostream>

int n;

struct X{
	X(int d_):d{d_}{
		++n;
		std::cout<<"Constructor called\n";
	}
	X(const X& x){
		++n; //  if the copy constructor has side effects, copy elision can change program behavior
		d = x.d;
		std::cout<<"Copy constructor called\n";
	}
	X(X&& x){
		d = x.d;
		std::cout<<"Move constructor called\n";
	}
	int d;
};

X returnX7(){
	return X(7);
}

int copy_elision(){

	/*
	 * copy elision refers to a compiler optimization technique that eliminates unnecessary
	 * copying of objects. It can be disabled using flag -fno-elide-constructors
	 */

	X x1(7); // ordinary constructor called.

	std::cout<<"\n";

	X x2(x1); // copy constructor called.

	std::cout<<"\n";

	X x3 = 7; // only ordinary constructor called when copy-elision is enabled.

	std::cout<<"\n";

    try{

    	// the exception object is considered to be an lvalue argument [2]
    	// only ordinary constructor called when copy-elision is enabled.
		throw X(7);

	}catch(const X& x){

		std::cout<<"x.d="<<x.d<<"\n";

	}catch(...){

		std::cout<<"ellipsis catch\n";
	}

	std::cout<<"\n";

	/*
	 * return value optimization (RVO) is a compiler optimization that involves eliminating
	 * the temporary object created to hold a function's return value.
	 */
	X x4 = returnX7(); // only ordinary constructor called when copy-elision is enabled.

	return 0;
}
