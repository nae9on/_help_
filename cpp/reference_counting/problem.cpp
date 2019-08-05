/*
 * problem.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: akadar
 */

/*
 * The basic scope rules in C++ play an important role in memory management.
 * Automatic variables (including references to them) get deleted when they go out of scope.
 * Similarly, pointer variables (including references to them) get deleted when they go out
 * of scope.
 *
 * However there can be following two problems:
 *
 * 1. Memory Leaks: The pointer variable is deleted (when it goes out of scope) but
 * the memory pointed to by the pointer variable is not explicitly de-allocated.
 *
 * 2. Unallocated memory access: The memory pointed to by a pointer variable is
 * de-allocated using the delete operator, but there are additional pointer variables
 * pointing to the block of memory which are not set to nullptr.
 *
 *
 */

#include <iostream>

class A{

};

void do_something(A* ptr){

}

A* func(){
	A* ptr = new A;
	return ptr;
}

int problem(){
	std::cout<<"In Main\n";

	A* ptr1 = new A;
	delete ptr1;

	A* ptr2 = func();
	A* ptr3 = ptr2;
	delete ptr2; // What if this statement is commented? Check with Valgrind!

	do_something(ptr3); // ptr3 is a dangling pointer

	std::cout<<"Exiting Main\n";
	return 0;
}
