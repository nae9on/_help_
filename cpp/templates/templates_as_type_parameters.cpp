/*
 * templates_as_type_parameters.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: akadar
 *
 *  This example demonstrates the use of passing templates as type parameters.
 *  We can pass a type parameter which is itself a template dependent on another type.
 *
 *  This example also demonstrates the difference between partial and complete specializations.
 *  Specializations in which all parameters are specialized are complete specializations.
 *  If only some of the parameters are specialized, it is called a partial specialization.
 */

#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>


/*
 * Example: passing templates as type parameters
 * In the example agreegate2 in value_type.cpp, the ::value_type of STL
 * containers is used to obtain the return type in the aggregator. Furthermore,
 * auto makes life easy.
 * However, it is possible to define the same aggregator (without using modern C++
 * features) by passing templates as type parameters.
 */

/*
 * Explanation
 * Here a container type needs to be passed which itself is a template dependent on
 * a value type and allocator type.
 *
 * T is value_type
 * A is some_allocator<T>
 * C is some_container<T,some_allocator<T>>
 */
template <typename T, template<typename> class A, template<typename,typename> class C>
T aggreegate(const C<T,A<T>>& c, T init = 0) {

	std::cout<<"Aggregate with templates as type parameters instantiated.\n";
	std::cout<<"T = "<<typeid(T).name()<<" A = "<<typeid(A<T>).name()
			<<" C = "<<typeid(C<T,A<T>>).name()<<"\n";

	T sum = init;

	// typename keyword in the next line provides a hint to the compiler
	// that C<char,A<char>>::const_iterator is a type
	using iterator = typename C<T,A<T>>::const_iterator;

	for (iterator it=c.cbegin(); it!=c.cend(); ++it) {
		sum+=*it;
	}

	return sum;
}

/*
 * Example: partial specialization.
 * T is char
 * A is some_allocator<char>
 * C is some_container<char,some_allocator<char>>
 */
template <template<typename> class A, template<typename,typename> class C>
std::string aggreegate(const C<char,A<char>>& c, char init) {

	std::cout<<"Aggregate as a partial specialization is instantiated.\n";
	std::cout<<"T = "<<typeid(char).name()<<" A = "<<typeid(A<char>).name()
			<<" C = "<<typeid(C<char,A<char>>).name()<<"\n";

	std::string sum{init};

	using iterator = typename C<char,A<char>>::const_iterator;
	for (iterator it=c.cbegin(); it!=c.cend(); ++it) {
		sum.push_back(*it);
	}

	return sum;
}

/*
 * Example: complete specialization.
 * T is char
 * A is std::allocator<char>
 * C is std::vector<char,std::allocator<char>>
 */
template <>
std::string aggreegate(const std::vector<char, std::allocator<char>>& c, char init) {

	std::cout<<"Aggregate as a complete specialization is instantiated.\n";
	std::cout<<"T = "<<typeid(char).name()<<" A = "<<typeid(std::allocator<char>).name()
			<<" C = "<<typeid(std::vector<char, std::allocator<char>>).name()<<"\n";

	std::string sum{init};

	using iterator = std::vector<char,std::allocator<char>>::const_iterator;

	for (iterator it=c.cbegin(); it!=c.cend(); ++it) {
		sum.push_back(*it);
	}

	return sum;
}

int main() {

	// Note normally allocator type defaults to allocator<T>
	std::vector<int,std::allocator<int>> x1{10,20,30};
	std::list<char,std::allocator<char>> x2{'A','L','I'};
	std::vector<char,std::allocator<char>> y{'A','L','I'};

	std::cout<<"Sum = "<<aggreegate<int, std::allocator, std::vector>(x1,100)<<"\n";

	// Automatic type deduction of template parameters
	std::cout<<"Sum = "<<aggreegate(x1,100)<<"\n";

	std::cout<<"Sum = "<<aggreegate(x2,'a')<<"\n";

	std::cout<<"Sum = "<<aggreegate(y,'a')<<"\n";

	return 0;
}
