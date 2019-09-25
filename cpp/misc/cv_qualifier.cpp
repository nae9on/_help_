/*
 * cv_qualifier.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: akadar
 *
 * In auto type deduction, when is the cv-qualifier dropped?
 */

#include <iostream>
#include <typeinfo>

int cv_qualifier(){

	/*
	 * Does auto retrieve cv-qualifier?
	 * auto deduction works the same as template deduction for most cases.
	 */

	std::cout<<"Begin main\n";

	int i = 1;
	const int j = 1;

	auto i1 = i;
	i1++; // OK, i1 retrieves the type and is a copy of i.
	auto& i2 = i;
	i2++; // OK, i2 retrieves the type and is a ref to i.
	auto j1 = j;
	j1++; // OK, j1 retrieves the type, drops the cv-qualifier and is a copy of j.
	auto& j2 = j;
	//j2++; // NOT OK, j2 retrieves the type, keeps the cv-qualifier and is a ref to j.
	std::cout<<"i = "<<i<<" j = "<<j<<"\n";

	int* ip = &i;
	const int* jp = &j;

	auto ip1 = ip;
	(*ip1)++; // OK, ip1 retrieves the type and is a copy of ip.
	auto& ip2 = ip;
	(*ip2)++; // OK, ip2 retrieves the type and is a ref to ip.
	auto jp1 = jp;
	//(*jp1)++; // NOT OK, jp1 retrieves the type, keeps the cv-qualifier and is a copy of jp.
	auto& jp2 = jp;
	//(*jp2)++; // NOT OK, jp2 retrieves the type, keeps the cv-qualifier and is a ref to jp.

	std::cout<<j2<<jp1<<jp2<<"\n";
	std::cout<<"End main\n";

	return 0;
}


