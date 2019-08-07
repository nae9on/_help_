/*
 * problem.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: akadar
 *
 *  Two most common problems related to memory management in C++.
 */

/*
 * The basic scope rules in C++ play an important role in memory management.
 * Automatic variables (including pointers and references) get deleted when they go out of scope.
 * This is because automatic variables are allocated on a stack (sometimes in registers too!).
 *
 * However there can be following two problems:
 *
 * 1. Memory Leak: A pointer variable is deleted when it goes out of scope but
 * the memory pointed to by the pointer variable is not explicitly deallocated.
 *
 * 2. Unallocated memory access: The memory pointed to by a pointer variable is
 * deallocated using the delete operator, but there may be additional pointer
 * variables pointing to the same block of memory.
 *
 */

#include <iostream>

struct A{
	A(int x_): x{x_} {}
	int x;
};

void print_A(A* ptr){
	std::cout<<"In A, x = "<<ptr->x<<"\n";

}

A* func(){
	A* ptr = new A(10);
	return ptr;
}

int problem(){
	std::cout<<"In Main\n";

	A* ptr1 = new A(7);
	print_A(ptr1);
	delete ptr1;

	A* ptr2 = func();
	A* ptr3 = ptr2;
	print_A(ptr2);
	print_A(ptr3);
	delete ptr2; // What if this statement is commented? Check with Valgrind!

	// ptr3 is a dangling pointer after deleting ptr2
	// invalid memory address read. Valgrind complaints!
	//print_A(ptr1);

	std::cout<<"Exiting Main\n";
	return 0;
}
