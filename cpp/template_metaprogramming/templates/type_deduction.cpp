/*
 * type_deduction.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: akadar
 *
 *  This example demonstrates template type deduction for function templates.
 *  Note: Class Template Argument Deduction (CTAD) is a C++17 core language feature.
 *
 *  References:
 *  [1] Effective Modern C++ - Scott Meyers (Item 1-4)
 */

#include <iostream>
#include <vector>
#include <typeinfo> // for typeid(T).name()
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

template<typename T>
void f(T& a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void g(T&& a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void h(T a){
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void add(T a, T b) {
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

template<typename T>
void add(std::initializer_list<T> l, T init) {
	std::cout<<__func__<<", T = "<<type_id_with_cvr<T>().pretty_name()<<"\n";
}

int type_deduction(){

	int x1{0};
	const int x2{0};
	const int& x3{0};

	// Case 1
	std::cout<<"Case 1\n";
	f(x1);
	f(x2);
	f(x3);

	// Case 2
	std::cout<<"Case 2\n";
	g(x1);
	g(x2);
	g(x3);

	// Case 3
	std::cout<<"Case 3\n";
	h(x1);
	h(x2);
	h(x3);

	std::cout<<"**************************************************\n";

	int* y1 = &x1;
	const int* y2 = &x2;
	const int* const y3 = &x3;

	// Case 1
	std::cout<<"Case 1\n";
	f(y1);
	f(y2);
	f(y3);

	// Case 2
	std::cout<<"Case 2\n";
	g(y1);
	g(y2);
	g(y3);

	// Case 3
	std::cout<<"Case 3\n";
	h(y1);
	h(y2);
	h(y3);

	std::cout<<"**************************************************\n";

	int m{0};
	double n{0.0};

	add<int>(m,m);
	add(m,m);
	add<double>(n,n);
	add(n,n);

	// Ambiguous type, therefore auto type deduction is not possible
	add<double>(m,n);

	/*
	 * When the template argument is explicitly specified, normal implicit
	 * conversions are done to convert the function arguments to the type of
	 * the corresponding function template parameters.
	 */
	add<int>(n,n);

    // sum of initializer_list
	add({1,2,3},0);
	add({1.0,2.0,3.0},0.0);

	// Ambiguous type, therefore auto type deduction is not possible
	add<double>({1.0,2.0,3.0},0);

	std::cout<<"**************************************************\n";

	return 0;
}
