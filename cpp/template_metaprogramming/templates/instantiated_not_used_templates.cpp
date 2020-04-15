/*
 * instantiated_not_used_templates.cpp
 *
 *  Created on: Jul 27, 2019
 *      Author: akadar
 *
 *  Note that the C++ standard requires a template definition to be parsed,
 *  irrespective of whether the template is used in the code or not.
 *  Failure to parse must be diagnosed regardless of instantiation.
 *
 *  A class template (and all its members) can be explicitly instantiated
 *  without using them in the code. Why is this useful?
 *  extern keyword can be used to prevent the automatic instantiation of
 *  class members.
 *
 *  Reference:
 *  https://docs.microsoft.com/en-us/cpp/cpp/explicit-instantiation?view=vs-2019
 *  https://stackoverflow.com/questions/2351148/explicit-instantiation-when-is-it-used
 */

#include <iostream>

// compiler will parse the definition of class X, even when it is not used in the code.
template<typename T> class X{
	// int x = y; // Error y is un-defined.
};

// Normal class template
template<typename T, int N> class Y{
	public:
	Y(){
		std::cout<<"Constructor of Y called\n";
	}
private:
};

/*
 * class Y is explicitly instantiated for types double and value=6 even though
 * it is not used in the code. All its member functions are also instantiated.
 * No memory is however reserved for any object.
 *
 */
template class Y<double, 6>;

// Error since Y<T, N>::Y() [with T = double; int N = 6] is already instantiated.
//template Y<double, 6>::Y(void);

/*
 * class Y is explicitly instantiated for types double and value=7.
 * However, none of its member functions are instantiated due to extern keyword.
 *
 */
extern template class Y<double, 7>;
//constructor of class Y for types double and value=7 is explicitly instantiated.
template Y<double, 7>::Y(void);

int main_instantiated_not_used_templates(){
    std::cout<<"In main\n";
	return 0;
}
