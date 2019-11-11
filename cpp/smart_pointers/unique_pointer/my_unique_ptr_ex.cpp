/*
 * my_unique_ptr_ex.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: akadar
 *
 *  Reference:
 *  https://docs.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=vs-2019
 */

/*
 * problem 1. Memory Leak is solved.
 * problem 2. Unallocated memory access is solved.
 * However, it does not allow shared ownership (refer to std::weak_ptr)
 */

#include <iostream>
#include <memory>

/*
 * my_unique_ptr class wraps a 'raw' C++ pointer, to manage
 * the lifetime of the object being pointed to.
 *
 */
template <typename T>
class my_unique_ptr{
public:

	my_unique_ptr(){
		raw = nullptr;
	}

	explicit my_unique_ptr(T* t){
		raw = t;
	}

	/*
	 * Copy constructor and copy assignment op are disabled because for unique pointers
	 * ownership cannot be shared. However default move constructors and move assignment
	 * are fine because ownership can be transferred/moved.
	 */

	// copy constructor disabled (same as for std::unique_ptr)
	explicit my_unique_ptr(const my_unique_ptr<T>& raw_) = delete;

	// copy assignment disabled (same as for std::unique_ptr)
	my_unique_ptr<T>& operator=(const my_unique_ptr<T>& raw_) = delete;

	my_unique_ptr(my_unique_ptr<T>&& raw_) = default;

	my_unique_ptr<T>& operator=(my_unique_ptr<T>&& raw_) = default;

	// member selection operator
	T* operator->(){
		return raw;
	}

	// dereference operator
	T operator*(){
		return *raw;
	}

	~my_unique_ptr(){
		delete raw;
	}

	void reset(T* raw_){
		delete raw;
		raw = raw_;
	}

	// Other member functions must be overloaded.

private:
	T* raw;
};

struct A1{
	A1(int x_): x{x_} {}
	int x;
};

A1* func1(){
	A1* ptr = new A1(10);
	return ptr;
}

int my_unique_ptr_ex(){

	my_unique_ptr<A1> ptr1(new A1(7));
	std::cout<<"In A, x = "<<ptr1->x<<"\n";

	my_unique_ptr<A1> ptr2(nullptr);
	ptr2.reset(func1());
	std::cout<<"In A, x = "<<(*ptr2).x<<"\n";

	// my_unique_ptr<A1> ptr3(ptr2); // Error, copy constructor disabled
	// my_unique_ptr<A1> ptr4; ptr4 = ptr2; // Error, copy assignment disabled

	my_unique_ptr<A1> ptr5 = std::move(ptr2); // OK, move constructor called
	my_unique_ptr<A1> ptr6; ptr6 = std::move(ptr2); // OK, move assignment called

	return 0;
}
