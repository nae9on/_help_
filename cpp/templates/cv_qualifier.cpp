/*
 * cv_qualifier.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: akadar
 *
 *  In template type deduction, when is the cv-qualifier dropped?
 *
 */

#include <iostream>
#include <typeinfo>

template<typename T> void deduce(T x){
	static int count = 0;
	count++;
	x++;
	//(*x)++;
	std::cout<<"In deduce, type is "<<typeid(T).name()<<" count = "<<count<<"\n";
}

template<typename T> void deduce_ref(T& x){
	static int count = 0;
	count++;
	//x++;
	//(*x)++;
	std::cout<<"In deduce_ref, type is "<<typeid(T).name()<<" count = "<<count<<"\n";
}

int cv_qualifier(){

	int i = 1;
	const int j = 1;
	int* ip = &i;
	int* const jp = &i;

	// “i” means “int”, “Pi” means “int*” and “PKi” means “int const*”  for GNU and Clang compilers

	deduce(i); // calls deduce<int>
	deduce(j); // calls deduce<int>, const is dropped with pass by copy
	deduce_ref(i); // calls deduce_ref<int>
	deduce_ref(j); // calls deduce_ref<const int> // const is kept with pass by ref


	deduce(ip); // calls deduce<int*>
	deduce(jp); // calls deduce<int const*>, const is dropped with pass by copy
	deduce_ref(ip); // calls deduce_ref<int*>
	deduce_ref(jp); // calls deduce_ref<int const*> // const is kept with pass by ref

	return 0;
}
