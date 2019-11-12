/*
 * basic_shared_ex.cpp
 *
 *  Created on: Nov 11, 2019
 *      Author: akadar
 */

#include <iostream>
#include <memory>

class X1{};

class Y{
public:
	Y(){std::cout<<"Y::ctor called\n";}
	~Y(){std::cout<<"Y::dtor called\n";}
};

int basic_shared_ex(){

	std::unique_ptr<X1> uptr(new X1);
	//std::unique_ptr<X1> uptr_copy(uptr); // Error

	std::shared_ptr<Y> sptr(new Y); // counter = 1
	std::shared_ptr<Y> sptr_copy1(sptr); // OK, shared ownership, counter = 2
	std::shared_ptr<Y> sptr_copy2; // owns nullptr
	sptr_copy2 = sptr; // OK, shared ownership, counter = 3

	sptr_copy2.reset(); // counter = 2
	sptr_copy1.reset(); // counter = 1
	sptr.reset(); // counter = 0 and thus destructor called

	std::cout<<"End main\n";
	return 0;
}
