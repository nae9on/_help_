/*
 * delegation_vs_inheritance.cpp
 *
 *  Created on: Aug 13, 2019
 *      Author: akadar
 *
 * Reference: https://en.wikipedia.org/wiki/Delegation_pattern
 */

/*
 * What is delegation?
 *
 * The delegation pattern allows composition of two objects to achieve similar
 * code reuse capabilities as inheritance. The two objects are referred to as
 * receiving object and delegate object respectively.
 *
 * The receiving object receives the original request which it delegates to the
 * delegate object (also called handler) and in doing so is reusing the handlers
 * code. This is similar to a derived class referring to it's base class in
 * inheritance except in delegation there is no polymorphic relationship between
 * the classes.
 *
 * From the Introduction to Gamma et al. 1994
 * Delegation is a way to make composition as powerful for reuse as inheritance.
 * In delegation, two objects are involved in handling a request: a receiving object
 * delegates operations to its delegate. This is analogous to subclasses deferring
 * requests to parent classes. But with inheritance, an inherited operation can always
 * refer to the receiving object through the this member variable in C++. To achieve
 * the same effect with delegation, the receiver passes itself to the delegate to let
 * the delegated operation refer to the receiver.
 *
 * Advantages over inheritance:
 * 1. It does not force the receiver to except all the methods of the base class
 * for instance addPrinter/removePrinter method is not needed in receiver class.
 * 2. When the base class is final and cannot be extended, inheritance is not
 * an option.
 *
 * Disadvantages:
 * 1. Unlike inheritance, delegation doesn’t facilitate dynamic polymorphism.
 * 2. Receiver class (ie. adobe_pdf_print) cannot be passed to an existing API
 * expecting a delegate class (i.e. printer).
 */

#include <iostream>
#include <stack>

// Example using inheritance
class printer{
public:
	printer(std::string defaultPrinter = "LaserJet3512"){
		printer_name.push(defaultPrinter);
	}
	void print(){
		std::cout<<"Printing to printer "<<printer_name.top()<<"\n";
	}
	void addPrinter(std::string pname){
		printer_name.push(pname);
	}
	void removePrinter(){
		printer_name.pop();
	}
private:
	std::stack<std::string> printer_name;
};

class adobe_pdf_print1: public printer{
	// Inherits the print method of the base class.
};

// Example using delegation
class adobe_pdf_print2{
public:
	adobe_pdf_print2(): ptr{nullptr}{}
	void setPrinter(printer* ptr_){
			ptr = ptr_;
		}
	void print(){
		// print method of the receiver class does not do much but
		// delegate the call to the delegate class method.
		// Note the receiver class can also be passed using this pointer.
		ptr->print();
	}
	~adobe_pdf_print2(){
	}
private:
	printer* ptr;
};

int delegation_vs_inheritance(){
	adobe_pdf_print1 x;
	x.print();

	printer p;
	adobe_pdf_print2 y;
	y.setPrinter(&p);
	y.print();

	/*
	 * Note that in this example, receiving class object (y) does not control
	 * life cycle of delegate class object (p). The two objects can stay independent
	 * of each other.
	 */

	return 0;
}
