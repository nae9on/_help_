/*
 * cv_qualifier.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: akadar
 *
 *
 *  Does auto preserve cv-qualifiers?
 *  auto type deduction works the same was as template deduction for most cases.
 *
 *  References:
 *  [1] Effective Modern C++ - Scott Meyers (Item 1-4)
 */

#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

int cv_qualifier(){

	int i = 1;
	const int j = 1;

	auto i1 = i;
	std::cout<<"Type i1 is "<<type_id_with_cvr<decltype(i1)>().pretty_name()<<"\n";
	auto& i2 = i;
	std::cout<<"Type i2 is "<<type_id_with_cvr<decltype(i2)>().pretty_name()<<"\n";
	auto j1 = j;
	std::cout<<"Type j1 is "<<type_id_with_cvr<decltype(j1)>().pretty_name()<<"\n";
	auto& j2 = j;
	std::cout<<"Type j2 is "<<type_id_with_cvr<decltype(j2)>().pretty_name()<<"\n";

	int* ip = &i;
	const int* jp = &j;

	auto ip1 = ip;
	std::cout<<"Type ip1 is "<<type_id_with_cvr<decltype(ip1)>().pretty_name()<<"\n";
	auto& ip2 = ip;
	std::cout<<"Type ip2 is "<<type_id_with_cvr<decltype(ip2)>().pretty_name()<<"\n";
	auto jp1 = jp;
	std::cout<<"Type jp1 is "<<type_id_with_cvr<decltype(jp1)>().pretty_name()<<"\n";
	auto& jp2 = jp;
	std::cout<<"Type jp2 is "<<type_id_with_cvr<decltype(jp2)>().pretty_name()<<"\n";

	return 0;
}
