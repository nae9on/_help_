/*
 * nullptr_exception.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: akadar
 */

/*
 * There is no "null pointer exception" in C++. The only exceptions we can catch
 * are the exceptions explicitly thrown by throw expressions (plus some standard C++
 * exceptions thrown intrinsically by standard operator new, dynamic_cast etc). There
 * are no other exceptions in C++.
 *
 * Dereferencing null pointers, division by zero etc does not generate exceptions in
 * C++, it produces undefined behavior. If one wants exceptions thrown in cases like
 * that it is the responsibility of the developer to manually detect these conditions
 * and throw exceptions explicitly.
 */

#include <iostream>
#include <exception>

class null_exception: public std::exception{
public:
	const char* what() const noexcept(true) override {
		return "NULL pointer exception";
	}

};

class A{
public:
	void print_A(){
		if(this==nullptr)
			throw null_exception();
		else
			std::cout<<"I am A";

		/*
		 * Note that it is undefined behavior to access "rank" in print_A when pointer
		 * object is nullptr.
		 */
	}
private:
	unsigned rank = 0;
};

int nullptr_exception(){

	A* x = nullptr;
	try{
		x->print_A();
	}
	catch(const std::exception& e){
		std::cout<<e.what();
	}

	return 0;
}
