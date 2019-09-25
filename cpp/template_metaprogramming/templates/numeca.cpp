/*
 * numeca.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>

static int count = 0;

template <typename T> void test(T){
	static int count = 0;
	// increment local count
	++count;
	// increment global count
	++::count;
	std::cout<<"Calling test with T, ";
	std::cout<<"local count = "<<count<<std::endl;
}

template <typename T> void test(T*){
	static int count = 0;
	// increment local count
	++count;
	// increment global count
	++::count;
	std::cout<<"Calling test with T pointer, ";
	std::cout<<"local count = "<<count<<std::endl;
}

int main_numeca()
{
	std::cout<<"In numeca\n";
	static int count = 0;

	int a{10}, b{11};
	float af{10.78}, bf{11.78};

	test(a);
	test(&a);
	test(b);
	test(&b);

	test(af);
	test(&af);
	test(bf);
	test(&bf);

	std::cout<<"main count = "<<count<<std::endl;

	// using the scope resolution operator to access the global count
	std::cout<<"global count = "<<::count<<std::endl;

	return 0;
}
