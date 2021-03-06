/*
 * constCast.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: akadar
 *
 * References:
 * https://docs.microsoft.com/en-us/cpp/cpp/const-cast-operator?view=vs-2019
 */

#include <iostream>
#include <string>

class person{
public:
	person(std::string name_): name{name_}{}
	void fun() const{
		// this->name = "fool"; // error

		// Note that in a const member function this = const person* this
		// const_cast makes it person*
		(const_cast<person*>(this))->name = "fool";
	}
	void print() {
		std::cout<<"\nI am "<<name;
	}
private:
	std::string name;
};

void print(int* x) {
	std::cout<<"\nx = "<<*x;
}

int constCast() {

	// 4 examples of usage of const_cast (only applicable for pointers)

	// Example 1
	int x = 1;
	//const int x = 0; // Note: It is undefined behavior to modify a const value.
	int const* y = &x;
	//(*y)++; // error
	int* p = const_cast<int*>(y);  // const_cast removes the const qualifier
	*p  = *p * 10;
	std::cout<<"x = "<<x;

	// Example 2
	// const_cast can be used to pass const data to a function that doesnot accept const.
	int const* z = &x;
	//print(z); // error
	print(const_cast<int*>(z));

	// Example 3
	// const_cast can be used to change non-const class members inside a const member function
	person p1("Tom");
	p1.print();
	p1.fun();
	p1.print();

	// Example 4
	// const_cast is considered safer than C-Stype casting.
	int xx = 2019;
	int const* yy = &xx;
	//char* pp = const_cast<char*>(yy); //error: invalid const_cast from 'const int*' to 'char*'
	char* pp = (char*)(yy); // not safe conversion from 'const int*' to 'char*'
	*pp = *pp * 10;
	std::cout<<"\nxx = "<<xx;

	return 0;
}
