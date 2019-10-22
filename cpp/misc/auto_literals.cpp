/*
 * auto_literals.cpp
 *
 *  Created on: May 24, 2019
 *      Author: akadar
 */

// [1] Ref https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=vs-2019

#include <iostream>
#include <cstring>
#include <string>

int auto_literals()
{
	std::cout<<"In auto\n\n";

	// Automatic type deduction of literals

	// Type deduction of char, string literals and std::string [1]
	auto xChar = 'x';
	auto str1 = "I am so long"; // C-style string literal
	auto str2 = std::string{"I am even longer"}; // std string literal

	std::cout<<"xChar = "<<xChar<<", size = "<<sizeof(xChar)<<" bytes"<<std::endl;
	std::cout<<"str1 = "<<str1<<", length = "<<strlen(str1)<<std::endl;
	std::cout<<"str2 = "<<str2<<", length = "<<str2.size()<<std::endl;

	std::cout<<"\n";

	// Type deduction of integer literals
	auto x_int = 10; x_int = 10.5; // (no suffix) defines int
	auto x_uint = 10u; x_uint = 10.5; // suffix u = unsigned int
	auto x_lint = 10l; x_lint = 10.5; // suffix l = long int
	auto x_ulint = 10ul; x_ulint = 10.5; // suffix ul = unsigned long int
	std::cout<<"x_int = "<<-1*x_int<<", size = "<<sizeof(x_int)<<" bytes"<<std::endl;
	std::cout<<"x_uint = "<<-1*x_uint<<", size = "<<sizeof(x_uint)<<" bytes"<<std::endl;
	std::cout<<"x_lint = "<<-1*x_lint<<", size = "<<sizeof(x_lint)<<" bytes"<<std::endl;
	std::cout<<"x_ulint = "<<-1*x_ulint<<", size = "<<sizeof(x_ulint)<<" bytes"<<std::endl;

	std::cout<<"\n";

	// Type deduction of float literals
	auto xFloat = 10.0f; // suffix f or F defines float
	auto xDouble = 10.0; // (no suffix) defines double
	auto xLongDouble = 10.0l; // suffix l or L defines long double
	std::cout<<"xFloat = "<<xFloat+0.5<<", size = "<<sizeof(xFloat)<<" bytes"<<std::endl;
	std::cout<<"xDouble = "<<xDouble+0.5<<", size = "<<sizeof(xDouble)<<" bytes"<<std::endl;
	std::cout<<"xLongDouble = "<<xLongDouble+0.5<<", size = "<<sizeof(xLongDouble)<<" bytes"<<std::endl;

	return 0;
}

