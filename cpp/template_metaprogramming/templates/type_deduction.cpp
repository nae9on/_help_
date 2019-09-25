/*
 * type_deduction.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: akadar
 *
 *  This example demonstrated the use of automatic type deduction for function templates.
 *  Note: Class Template Argument Deduction (CTAD) is a C++17 Core Language feature.
 */

// This example is not yet done

#include <iostream>
#include <vector>
#include <typeinfo>

template <typename T> T add(std::initializer_list<T> l, T init) {
	std::cout<<"Deduced template type argument = "<<typeid(T).name()<<"\n";
	T sum{init};
	for(const auto& e:l) sum = sum + e;
	return sum;
}

template <typename T> T add(T a, T b) {
	std::cout<<"Deduced template type argument = "<<typeid(T).name()<<"\n";
	return a+b;
}

int main_type_deduction(){

	int x1{1}, y1{2};
	double x2{101.1}, y2{104.2};
	std::string x3{"Ali"}, y3{" Kadar"};

	std::cout<<add<int>(x1,y1)<<"\n";
	std::cout<<add(x1,y1)<<"\n";

	std::cout<<add<double>(x2,y2)<<"\n";
	std::cout<<add(x2,y2)<<"\n";

	// Ambiguous type, therefore auto type deduction is not possible
	std::cout<<add<double>(x1,y2)<<"\n";

	/*
	 * When the template argument is explicitly specified, normal implicit
	 * conversions are done to convert the function arguments to the type of
	 * the corresponding function template parameters.
	 */
	std::cout<<add<int>(x2,y2)<<"\n";

    // sum of initializer_list
	std::cout<<add({1,2,3},0)<<"\n";
	std::cout<<add({1.0,2.0,3.0},0.0)<<"\n";

	// Ambiguous type, therefore auto type deduction is not possible
	std::cout<<add<double>({1.0,2.0,3.0},0)<<"\n";

	return 0;
}
