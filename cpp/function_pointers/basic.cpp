/*
 * basic.cpp
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

// type 1 return with using
double_ptr1 init_array1(size_t n, double* x, double (*f)(double)){
	for (size_t i=0; i<n; i++) x[i] = (*f)(x[i]);
	return &mysqrt;
}

// type 2 return with typedef
double_ptr2 init_array2(size_t n, double* x, double (*f)(double)){
	for (size_t i=0; i<n; i++) x[i] = (*f)(x[i]);
	return &mysqrt;
}

void print_array(size_t n, double* x){
	for (size_t i=0; i<n; i++) std::cout<<x[i]<<" ";
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
	double (*ptr1)(double); // declaring a function pointer of type double_ptr1
	double (*ptr2)(double); // declaring another function pointer of type double_ptr1
	double (*ptr3)(double); // declaring yet another function pointer of type double_ptr1

	// assigning the function pointer to the address of the executable code
	ptr1 = &square;
	ptr2 = &mysqrt;

	double x[] = {1,2,3};

	std::cout<<"Square of 2 is "<<(*ptr1)(2)<<"\n";
	std::cout<<"Square root of 2 is "<<(*ptr2)(2)<<"\n";

	ptr3 = init_array1(3,x,ptr1);
	print_array(3,x);
	ptr3 = init_array1(3,x,ptr3);
	print_array(3,x);


	// C++'s most vexing parse
	mypi (*fp)(); // Declaring a pointer to a function accepting void and returning mypi.
	fp = &getPIObj;

	// Note all the forward declarations are the same.
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
