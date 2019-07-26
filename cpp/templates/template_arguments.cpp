/*
 * template_arguments.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>

/*
 * Aggregator for char container, it is a template partial specialization.
 * Note: Specializations in which all parameters are specialized are complete specializations.
 * If only some of the parameters are specialized, it is called a partial specialization.
 */
template <template<typename> class A, template<typename,typename> class Vec>
std::string aggreegate(const Vec<char,A<char>>& c, char init = 'x') {
	std::string sum{init};
	// typename keyword in the next line provides a hint to the compiler
	// that Vec<char,A<char>>::const_iterator is a type
	using iterator = typename Vec<char,A<char>>::const_iterator;
	for (iterator it=c.cbegin(); it!=c.cend(); ++it) {
		sum.push_back(*it);
	}
	return sum;
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
T aggreegate(const Vec<T,A<T>>& c, T init = 0) {
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

	std::cout<<"Sum = "<<aggreegate<int, std::allocator, std::vector>(c3,100)<<"\n";

	// Automatic type deduction of template arguments
	std::cout<<"Sum = "<<aggreegate(c3,100)<<"\n";

	std::cout<<"Sum = "<<aggreegate(std::vector<char>{'A','L','I'})<<"\n";

	return 0;
}
