/*
 * staticCast.cpp
 *
 *  Created on: May 26, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://docs.microsoft.com/en-us/cpp/cpp/static-cast-operator?view=vs-2019
 */

#include <iostream>

class base
{
public:
    // virtual member function added to make base a run-time polymorphic type
    virtual void print(){}
    virtual ~base(){}
};

class derived: public base{};

void* my_allocator(std::size_t n)
{
    return std::malloc(n);
}

derived* doSomethingWithBasePointer(void* p)
{
    // dynamic_cast cannot be used here since p is not a run-time polymorphic type
    base* pb = static_cast<base*>(p);
    return dynamic_cast<derived*>(pb);
}

int staticCast()
{
	/*
	 * static_cast does no run-time type check [1].
	 *
	 * static_cast relies exclusively on the information provided in the cast statement
	 * and can therefore be unsafe. It is left to the programmer to verify that the result
	 * of a static_cast conversion is safe.
	 *
	 * static_cast is typically used in performance-critical code and when the desired
	 * conversion is inherently low-level.
	 */

    // Example uses of static_cast

    /*
     * Usage 1: Mostly they are used to convert numeric data types such as ints to enums
     * or floats to ints, when the programmer is certain of the data types involved in the conversion.
     */
	int x = 7081989;
	float fx = static_cast<float>(x); // int to float conversion is safe
	char ch = static_cast<char>(x); // programmer is responsible for the loss of bits.
	float x2 = 3.141; // implicit conversion from double to float can result into loss of precision
	double y2 = static_cast<double>(x2); // float to double conversion is safe
	(void) fx; (void) ch; (void) y2;

	/*
	 * Usage 2: conversion from base* to derived* in a class hierarchy.
	 * Because static_cast does no run-time type check, a cast to an ambiguous pointer in the
	 * class hierarchy will always succeed and return as if nothing were wrong. Therefore, for
	 * safety, use dynamic_cast (+ check for not nullptr) instead but at the expense of additional
	 * run-time cost.
	 */
	base* pb = new derived;
	derived* pd = static_cast<derived*>(pb); // OK safe here
    base* pb0 = new base;
    derived* pd0 = static_cast<derived*>(pb0); // Not safe here and a recepie for disaster
	(void) pd; (void) pd0;

    /*
     * Usage 3: conversion from 'void*' to 'X*'
     * Handle to unformatted memory (returned by operator new and malloc) is a void*.
     * Since the memory does not have a type (because it does not have a properly constructed
     * object in it yet), it is type-less.
     * Note: dynamic_cast cannot be used on a void* since it requires a polymorphic operand.
     */
	//int* iptr = my_allocator(100); // error: invalid conversion from 'void*' to 'int*'
	int* iptr = static_cast<int*>(my_allocator(100)); // at your own risk!
	derived* pdd = doSomethingWithBasePointer(new derived);
	(void) iptr; (void) pdd;

	// Note: static_cast is better than a C-style cast for two reasons:
	// 1. They are checked by the compiler
	// 2. They are more readable and easy to spot
	char characters{'a'};
	int* ptr = (int*)&characters; // recipe for a disaster
	//int* ptr = static_cast<int*>&ch; // Error invalid static_cast from type 'char*' to type 'int*'
	*ptr = 123456789; // disaster
	(void) ptr;

	std::cout<<"End\n";
	return 0;
}


