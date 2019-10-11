/*
 * void_ptr.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: akadar
 */

#include <iostream>

class X{

};

int void_ptr(){

	// Usage example 1
	/*
	 * Its primary usage is dealing in unformatted memory. This is what operator new and malloc return
	 * i.e. a block of memory of a certain size. Since the memory does not have a type (because it does
	 * not have a properly constructed object in it yet), it is type-less.
	 */

	// For example refer to /operator_overloading/new.cpp

	return 0;
}


