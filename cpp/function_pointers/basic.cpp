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

int main1(){
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

	return 0;
}
