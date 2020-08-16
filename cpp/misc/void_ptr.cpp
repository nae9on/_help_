/*
 * void_ptr.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: akadar
 *
 *  No variable of type void can be specified — it is used primarily to declare functions
 *  that return no values or to declare generic pointers to untyped or arbitrarily typed data.
 */

#include <iostream>

void* my_allocator(std::size_t n)
{
    return std::malloc(n);
}

int void_ptr(){

	// Usage example 1
	/*
	 * Its primary usage is dealing in unformatted memory. This is what operator new and malloc return
	 * i.e. a block of memory of a certain size. Since the memory does not have a type (because it does
	 * not have a properly constructed object in it yet), it is type-less.
	 *
	 * For example refer to /operator_overloading/new.cpp
	 */
    //int* iptr = my_allocator(100); // error: invalid conversion from 'void*' to 'int*'
    int* iptr = static_cast<int*>(my_allocator(100)); // at your own risk!
    (void) iptr;
	
	/*
	 * void* are quite useful when passing pointer arguments to callback functions
	 * in the context of a class hierarchy (for basic example refer staticCast.cpp)
	 *
	 * Some more useful interesting examples are provided here
	 * https://docs.opencv.org/master/db/df6/tutorial_erosion_dilatation.html
	 * https://github.com/nae9on/_help_/blob/master/opencv/core_module/trackbar.cpp
	 */

	return 0;
}
