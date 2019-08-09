/*
 * diamond_problem.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 *
 *  Reference: https://en.wikipedia.org/wiki/Virtual_inheritance
 */

#include <iostream>

class A{
public:
	void print_name(){
		std::cout<<"I am class A\n";
	}
};

// without virtual keyword, print_name in BC is ambiguous
class B: public virtual A{

};

class C: public virtual A{

};

// class BC is an example of multiple inheritance, as it combines independent
// classes B and C that share the same base class A.
class BC: public B, public C{

};

int main(){
	BC obj;
	obj.print_name();
	return 0;
}
