/*
 * my_shared_pointer_ex.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: akadar
 *
 *  Reference:
 *  https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-raw-instances?view=vs-2019
 */

/*
 * problem 1. Memory Leak is solved.
 * problem 2. Unallocated memory access is solved.
 * It allows shared ownership via reference counting.
 */

#include <iostream>
#include <memory>

// class for reference counting
struct counter{
public:
	counter(){
		count = 1;
		std::cout<<"Counter constructed\n";
	}
	~counter(){
		std::cout<<"Counter de-constructed\n";
	}
	size_t count;
};

template<typename T>
class my_shared_pointer{
public:

	my_shared_pointer(){
		ctr = nullptr;
		raw = nullptr;
	}

	explicit my_shared_pointer(T* t){
		ctr = new counter();
		raw = t;
	}

	void dec(){
		--(ctr->count);
		if(ctr->count==0) {
			delete ctr;
			delete raw;
		}
	}

	explicit my_shared_pointer(const my_shared_pointer<T>& in){
		if(in.ctr!=nullptr && in.raw!=nullptr)
		{
		ctr = in.ctr;
		raw = in.raw;
		++(ctr->count);
		}
	}

	my_shared_pointer<T>& operator=(const my_shared_pointer<T>& right){
		if(ctr==right.ctr && raw==right.raw){
		}
		else if(right.ctr==nullptr && right.raw==nullptr){
			dec();
			ctr = nullptr;
			raw = nullptr;
		}
		else if(ctr==nullptr){
			ctr = right.ctr;
			raw = right.raw;
			++(ctr->count);
		}
		else{
			dec();
			ctr = right.ctr;
			raw = right.raw;
			++(ctr->count);
		}
		return *this;
	}

	// implement move semantics

	// member selection operator
	T* operator->(){
		return raw;
	}

	// dereference operator
	T operator*(){
		return *raw;
	}

	~my_shared_pointer(){
		if (ctr!=nullptr){
			if(ctr->count==1){
				delete ctr; // Warning delete can throw an exception
				delete raw; // Warning delete can throw an exception
			}else {
				--(ctr->count);
			}
		}
	}

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

int my_shared_pointer_ex(){

	using shared_pointer_version = my_shared_pointer<A2>;
	//using shared_pointer_version = std::shared_ptr<A2>;

	std::cout<<"In main\n";

	shared_pointer_version ptr1(new A2(7)); // ptr1 taking first-ownership of A2(7)
	std::cout<<"In A, x = "<<ptr1->x<<"\n";

	shared_pointer_version ptr2(func2()); // ptr2 taking first-ownership of A2(10)
	std::cout<<"In A, x = "<<(*ptr2).x<<"\n";

	std::cout<<"***************************\n";

	shared_pointer_version ptr3; // no ownership yet
	ptr3 = ptr2; // ptr3 sharing ownership of A2(10)

	std::cout<<"***************************\n";

	shared_pointer_version x0; // no ownership yet
	shared_pointer_version x1(new A2(1)); // x1 taking first-ownership of A2(1)
	shared_pointer_version x2(new A2(2)); // x2 taking first-ownership of A2(2)

	std::cout<<"***************************\n";

	shared_pointer_version y0; // no ownership
	shared_pointer_version y1(new A2(3)); // y1 taking first-ownership of A2(3)
	shared_pointer_version y2(new A2(4)); // y2 taking first-ownership of A2(4)

	std::cout<<"***************************\n";

	y1 = x1; // y1 taking ownership of A2(1), no one owns A2(3)

	std::cout<<"***************************\n";

	y2 = x1; // y2 taking ownership of A2(1), no one owns A2(4)

	std::cout<<"***************************\n";

	x1 = x0; // x1 taking ownership of nullptr

	std::cout<<"End main\n";

	return 0;
}
