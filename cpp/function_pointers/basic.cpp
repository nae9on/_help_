/*
 * basic.cpp
 *
 * Function pointers are typically used for implementing callbacks.
 * A callback is a pointer to a function, so if you want a processing function to notify you about some
 * event you pass a pointer to another function (the callback) to the processing function.
 * The processing function then calls the callback when appropriate. Callbacks have two fundamental flaws:
 * Firstly, they are not type-safe. We can never be certain that the processing function will call the callback
 * with the correct arguments. Secondly, the callback is strongly coupled to the processing function since the processing
 * function must know which callback to call. Because of these inherent drawbacks, function pointers are not popular
 * anymore for implementing callbacks. Better (type-safe and more flexible) mechanisms example Signals and Slots (Qt framework)
 * are more commonly used for implementing callbacks.
 *
 *  Created on: Aug 8, 2019
 *      Author: akadar
 */

#include <iostream>
#include <cmath>

using double_ptr1 = double (*)(double);
typedef double (*double_ptr2)(double);

double square(double x){
	return x*x;
}

double mysqrt(double x){
	return std::sqrt(x);
}

void init_array(size_t n, double* x, double (*f)(double)){
	for (size_t i=0; i<n; ++i) x[i] = (*f)(x[i]);
}

void print_array(size_t n, double* x){
	for (size_t i=0; i<n; ++i) std::cout<<x[i]<<" ";
	std::cout<<"\n";
}

class mypi{
public:
	mypi(): pi{3.141}{}
	double pi;
};

mypi getPIObj(){
	return mypi();
}

int basic(){

	// Following 3 statements are identical
	//double (*ptr)(double); // declaring a function pointer of type double_ptr1
	//double_ptr1 ptr;
	double_ptr2 ptr;

	// assigning the function pointer to the address of the executable code
	ptr = &square;
	std::cout<<"Square of 2 is "<<(*ptr)(2)<<"\n";

	ptr = &mysqrt;
	std::cout<<"Square root of 2 is "<<(*ptr)(2)<<"\n";

	double x[] = {1,2,3};

	init_array(3,x,ptr);
	print_array(3,x);

	// C++'s most vexing parse
	mypi (*fp)(); // Declaring a pointer to a function accepting void and returning mypi.
	fp = &getPIObj;

	// Note: all the forward declarations are the same.
	//mypi printPI(mypi (*fp_)()); // Version 1
	//mypi printPI(mypi(*)()); // Version 2
	//mypi printPI(mypi fp_()); // Version 3
	mypi printPI(mypi()); // Version 4

	// Version 4 can also be interpreted as copy-constructing printPI variable of type mypi.
	// but compiler parse's it as a function declaration.
	// This ambiguity is called C++'s most vexing parse.

	mypi obj = printPI(fp);
	std::cout<<"Pi = "<<obj.pi<<"\n";

	return 0;
}

mypi printPI(mypi (*fp)()){
	return (*fp)();
}
