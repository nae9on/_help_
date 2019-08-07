/*
 * shared_pointer.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: akadar
 *
 *  Reference:
 *  https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-raw-instances?view=vs-2019
 */

/*
 * problem 1. Memory Leaks is solved.
 * problem 2. Unallocated memory access is solved via reference counting.
 * std::shared_ptr provides a better solution.
 *
 */

#include <iostream>
#include <memory>

struct counter{
public:
	counter(){
		count = 1;
		std::cout<<"Counter constructed\n";
	}
	~counter(){
		std::cout<<"Counter deleted\n";
	}
	unsigned count;
};

// class for reference counting
template<typename T> class my_shared_pointer{
public:
	// default constructor
	my_shared_pointer(){
		ctr = nullptr;
		raw = nullptr;
	}

	// ordinary constructor
	explicit my_shared_pointer(T* t){
		ctr = new counter();
		raw = t;
	}

	// copy constructor
	explicit my_shared_pointer(const my_shared_pointer<T>& t){
		ctr = t.ctr;
		raw = t.raw;
		ctr->count++;
	}

	// copy assignment
	my_shared_pointer<T>& operator=(const my_shared_pointer<T>& t){
		if(ctr==t.ctr && raw==t.raw){
		}
		else if(t.ctr==nullptr && t.raw==nullptr){
			ctr->count = ctr->count-1;
			if(ctr->count==0) {
				delete ctr;
				delete raw;
			}
			ctr = nullptr;
			raw = nullptr;
		}
		else if(ctr==nullptr){
			ctr = t.ctr;
			raw = t.raw;
			ctr->count++;
		}
		else{
			ctr->count = ctr->count-1;
			if(ctr->count==0) {
				delete ctr;
				delete raw;
			}
			ctr = t.ctr;
			raw = t.raw;
			ctr->count++;
		}
		return *this;
	}

	// invocation operator
	T* operator->(){
		return raw;
	}

	// indirection operator
	T operator*(){
		return *raw;
	}

	~my_shared_pointer(){
		if (ctr!=nullptr){
			if(ctr->count==1){
				delete ctr; // Warning delete can throw an exception
				delete raw; // Warning delete can throw an exception
			}else {
				ctr->count = ctr->count-1;
			}
		}
	}

	// Other member functions must be overloaded.

private:
	counter* ctr;
	T* raw;
};

struct A2{
	A2(int x_): x{x_} {}
	int x;
};

A2* func2(){
	A2* ptr = new A2(10);
	return ptr;
}

int main(){
	std::cout<<"In main\n";

	// My basic solution.
	my_shared_pointer<A2> ptr1(new A2(7));
	std::cout<<"In A, x = "<<ptr1->x<<"\n";

	my_shared_pointer<A2> ptr2(func2());
	std::cout<<"In A, x = "<<ptr2->x<<"\n";

	my_shared_pointer<A2> ptr3;
	ptr3 = ptr2;

	// More fun
	my_shared_pointer<A2> x0; // no ownership
	my_shared_pointer<A2> x1(new A2(1)); // ownership of R1 is with x1
	my_shared_pointer<A2> x2(new A2(2)); // ownership of R2 is with x2

	my_shared_pointer<A2> y0; // no ownership
	my_shared_pointer<A2> y1(new A2(3)); // ownership of R3 is with y1
	my_shared_pointer<A2> y2(new A2(4)); // ownership of R4 is with y2

	y1 = x1; // y1 owns R1, no one owns R3 and therefore is freed.
	y2 = x1; // y2 owns R1, no one owns R4 and therefore is freed.
	x1 = x0; // x1 is set to nullptr, no one owns R1 and therefore is freed.*/

	std::cout<<"End main\n";
	return 0;
}
