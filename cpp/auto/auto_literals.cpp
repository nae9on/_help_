/*
 * auto_literals.cpp
 *
 *  Created on: May 24, 2019
 *      Author: akadar
 *
 *	Automatic type deduction of literals
 *
 *  References
 *  [1] https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=vs-2019
 *  [2] https://en.cppreference.com/w/cpp/language/integer_literal
 *  [3] https://en.cppreference.com/w/cpp/language/floating_literal
 */

#include <iostream>
#include <cstring>
#include <string>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

int auto_literals()
{
	// Type deduction of char, string literals and std::string [1]
	auto xChar = 'x';
	auto str1 = "I am so long"; // C-style string literal (i.e. char const*)
	auto str2 = std::string{"I am even longer and better"}; // std::string literal

	std::cout<<"xChar = "<<xChar<<", size = "<<sizeof(xChar)<<" bytes"
			 <<", Type is "<<type_id_with_cvr<decltype(xChar)>().pretty_name()<<std::endl;
	std::cout<<"str1 = "<<str1<<", length = "<<strlen(str1)<<", size = "<<sizeof(str1)<<" bytes"
			 <<", Type is "<<type_id_with_cvr<decltype(str1)>().pretty_name()<<std::endl;
	std::cout<<"str2 = "<<str2<<", length = "<<str2.size()<<", size = "<<sizeof(str2)<<" bytes"
		     <<",\nType is "<<type_id_with_cvr<decltype(str2)>().pretty_name()<<std::endl;

	std::cout<<"\n";

	// Type deduction of integer literals
	auto x_int = 10; x_int = 10.5; // (no suffix) defines int
	auto x_uint = 10u; x_uint = 10.5; // suffix u = unsigned int
	auto x_lint = 10l; x_lint = 10.5; // suffix l = long int, similarly suffix ll = long long int
	auto x_ulint = 10ul; x_ulint = 10.5; // suffix ul = unsigned long int, similarly suffix ull = unsigned long long int
	std::cout<<"x_int = "<<-1*x_int<<", size = "<<sizeof(x_int)<<" bytes"
			<<", Type is "<<type_id_with_cvr<decltype(x_int)>().pretty_name()<<std::endl;
	std::cout<<"x_uint = "<<-1*x_uint<<", size = "<<sizeof(x_uint)<<" bytes"
			<<", Type is "<<type_id_with_cvr<decltype(x_uint)>().pretty_name()<<std::endl;
	std::cout<<"x_lint = "<<-1*x_lint<<", size = "<<sizeof(x_lint)<<" bytes"
			<<", Type is "<<type_id_with_cvr<decltype(x_lint)>().pretty_name()<<std::endl;
	std::cout<<"x_ulint = "<<-1*x_ulint<<", size = "<<sizeof(x_ulint)<<" bytes"
			<<", Type is "<<type_id_with_cvr<decltype(x_ulint)>().pretty_name()<<std::endl;

	std::cout<<"\n";

	// Type deduction of float literals
	auto xFloat = 10.0f; // suffix f or F defines float
	auto xDouble = 10.0; // (no suffix) defines double, suffix d can also be used to define a double
	auto xLongDouble = 10.0l; // suffix l or L defines long double
	std::cout<<"xFloat = "<<xFloat+0.5<<", size = "<<sizeof(xFloat)<<" bytes"
			 <<", Type is "<<type_id_with_cvr<decltype(xFloat)>().pretty_name()<<std::endl;
	std::cout<<"xDouble = "<<xDouble+0.5<<", size = "<<sizeof(xDouble)<<" bytes"
			 <<", Type is "<<type_id_with_cvr<decltype(xDouble)>().pretty_name()<<std::endl;
	std::cout<<"xLongDouble = "<<xLongDouble+0.5<<", size = "<<sizeof(xLongDouble)<<" bytes"
			 <<", Type is "<<type_id_with_cvr<decltype(xLongDouble)>().pretty_name()<<std::endl;

	return 0;
}

