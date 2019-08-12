/*
 * diamond_problem.cpp
 *
 *  Created on: Aug 9, 2019
 *      Author: akadar
 *
 *  Reference: https://en.wikipedia.org/wiki/Virtual_inheritance
 */

/*
 * The diamond inheritance problem is an example of redundant inheritance.
 * When two classes B and C are derived from a common base class A, A is present in both
 * classes B and C. When class BC is derived from B and C combined, class BC inherits two identical
 * copies of A, but referred by two different ways. One is A derived through B and the other
 * is A derived through C. Therefore the presence of A in BC is ambiguous.
 *
 * This ambiguity can be resolved by using virtual inheritance i.e. B can be derived from A
 * using public virtual. Similarly C can be derived from A using public virtual. This ensures
 * that base class A is common throughout the hierarchy without any ambiguity.
 *
 * Note that the object size of class BC has two pointers to vtable instead of one,
 * one per inheritance hierarchy that virtually inherits A.
 *
 * Note that this is also an example of multiple inheritance.
 */

#include <iostream>

class A{
public:
	virtual void print_name(){
		std::cout<<"I am class A\n";
	}
	virtual ~A(){}
};

class B: public A{

};

class C: public A{

};

class BC: public B, public C{

};

int diamond_problem(){

	BC bc;
	B b;
	C c;

	A& a1 = b; // OK since both b and c contains sub-object of A.
	b.print_name(); // OK since both b and c contains members of A.

	//A& a= bc; // ambiguous since bc contains two sub-objects of A one via B and one via C.
	//bc.print_name(); // ambiguous since bc contains two members of A one via B and one via C.

	A& a = static_cast<B&>(bc); // OK resolved to sub-object of A via B.
	bc.B::print_name(); // OK resolved to print_name of A via B.

	// using the virtual keyword, the ambiguous presence of A in BC is resolved.

	return 0;
}
