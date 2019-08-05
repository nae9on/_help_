/*
 * invasive_counting.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: akadar
 *
 */

/*
 * A possible solution to the problem of reference counting
 * Reference:
 * https://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas
 *
 * This solution solves both the problems stated in problem.cpp
 * 1. Memory Leaks and 2. Unallocated memory access and also Valgrind is happy!
 * However, its not the best solution because of the following two reasons:
 * 1. The user has to remember to call increment and decrement as and when needed.
 * 2. The technique is invasive, as in the object itself keeps track of the refernce count.
 *
 */
#include <iostream>

class RefCount1{
public:
	RefCount1(): counter{0}{
		std::cout<<"Base class constructor called\n";
	}
	void increment() {
		std::cout<<"Counter incremented\n";
		counter++;
	}
	void decrement() {
		std::cout<<"Counter decremented\n";
		counter--;
		if (counter == 0) {
			delete this;
		}
	}
	unsigned getCounter(){
		return counter;
	}
	virtual ~RefCount1(){
		std::cout<<"Base class de-constructor called\n";
	}
private:
	unsigned counter;
};

class A1: public RefCount1{
public:
	A1(){
		std::cout<<"Derived class constructor called\n";
	}
	~A1(){
		std::cout<<"Derived class de-constructor called\n";
	}
};

A1* func1(){
	A1* ptr = new A1;
	ptr->increment();
	return ptr;
}

int invasive_counting(){
	std::cout<<"In Main\n";

	A1* ptr1 = new A1;
	ptr1->increment();

	A1* ptr2 = ptr1;
	ptr2->increment();

	// ptr1 no longer needed
	ptr1->decrement();

	// ptr2 no longer needed
	ptr2->decrement();

	std::cout<<"\n\n";

	A1* ptr3 = func1();

	// ptr3 no longer needed
	ptr3->decrement();

	std::cout<<"Exiting Main\n";
	return 0;
}
