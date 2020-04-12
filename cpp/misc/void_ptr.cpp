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
	
	/* void* are quite useful when passing pointer arguments to callback functions
	An interesting example is provided here
	https://docs.opencv.org/master/db/df6/tutorial_erosion_dilatation.html
	https://github.com/nae9on/_help_/blob/master/opencv/core_module/trackbar.cpp*/

	return 0;
}


