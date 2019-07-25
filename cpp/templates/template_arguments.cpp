/*
 * template_arguments.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>

// overloaded aggregator
char aggreegate(char init, const std::vector<char,std::allocator<char>>& c) {
	return 'a';
}

/*
 * In the example agreegate2 in value_type.cpp, the ::value_type of STL
 * containers is used to obtain the return type in the aggregator. Furthermore,
 * auto makes life easy.
 * However, it is possible to define aggregator without using these features as
 * by using template template parameters.
 * Tip use template template syntax to pass a parameter whose type is a template
 * dependent on another template.
 */

/*
 * Explanation
 * typename T is for char
 * template<typename> class A is for std::allocator<char>
 * template<typename,typename> class Vec is for std::vector<char,std::allocator<char>>
 */
template <typename T, template<typename> class A, template<typename,typename> class Vec>
T aggreegate(T init, const Vec<T,A<T>>& c) {
	T sum = init;
	using iterator = typename Vec<T,A<T>>::const_iterator;
	for (iterator it=c.cbegin(); it!=c.cend(); ++it) {
		sum+=*it;
	}
	return sum;
}

int main_template_arguments() {

	// Note normally allocator type defaults to allocator<T>
	std::vector<int,std::allocator<int>> c3{10,20,30};

	std::cout<<"Sum = "<<aggreegate<int, std::allocator, std::vector>(100,c3)<<"\n";

	// Automatic type deduction of template arguments
	std::cout<<"Sum = "<<aggreegate(100,c3)<<"\n";

	std::cout<<"Sum = "<<aggreegate('x',std::vector<char>{'y'})<<"\n";

	return 0;
}
