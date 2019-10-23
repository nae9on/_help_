/*
 * type_traits.cpp
 *
 *  Created on: Jul 29, 2019
 *      Author: akadar
 *
 * The aim is to write a pre-increment function which increments only short and int
 * types (with there type modifiers signed, unsigned and long).
 *
 * All integral types include bool, char, short, int (with there type modifiers).
 *
 * Another nice example is that of std::is_arithmetic when defining complex struct [3].
 *
 * References:
 * [1] http://blog.aaronballman.com/2011/11/a-simple-introduction-to-type-traits
 * [2] http://www.cplusplus.com/reference/type_traits/is_integral/
 * [3] Stroustrup, Bjarne. A Tour of C++. Chapter 4, Addison-Wesley Professional, 2018
 *
 */

/*
 * In debug mode, to catch programming errors, assert can be used. Normally assert is enabled
 * only in the debug mode and not in the release mode (for performance reasons).
 *
 * Therefore, this macro is designed to capture programming errors, not user or run-time errors,
 * since it is generally disabled after a program exits its debugging phase.
 *
 * defining macro NDEBUG before including cassert will disable assertion at run-time.
 */

//#define NDEBUG // uncomment to disable assert

#include <iostream>
#include <string>
#include <cassert>

// Simple example of a templated pre-increment function which is supposed to
// pre-increment only int's and short's
template<typename T> void pre_increment(T& x){
	++x;
}

// assert is evaluated at run-time
template<> void pre_increment(char& x){
	assert(false && "Illegal to pre-increment char");
}
template<> void pre_increment(double& x){
	assert(false && "Illegal to pre-increment double");
}
// what if T is bool, float, double etc? The solution is not practical.

// Better version of templated pre_increment function
template<typename T>
struct is_pre_incrementable {
  static constexpr bool value = false;
};
template<>
struct is_pre_incrementable<int> {
  static constexpr bool value = true;
};
template<typename T> void better_pre_increment(T& x){
	static_assert(is_pre_incrementable<T>::value, "Illegal to pre_increment ");
	++x;
}
// only int is allowed, what if T is long int or short? The solution is not practical.

// Best version of templated pre_increment function using std::is_integral
// std::is_integral is a trait class that identifies whether T is an integral type [2].
template<typename T> constexpr bool is_int_or_short() {
	// sizeof test excludes bool, char along with there type modifiers.
	return (std::is_integral<T>::value && sizeof(T)>=2);
}
template<typename T> void smart_pre_increment(T& x){
	// Note that having is_int_or_short makes the code hide implementation details.
	static_assert(is_int_or_short<T>(),"Illegal to pre_increment types that are not int or short");
	++x;
}

int type_traits(){

	std::cout<<"In main\n";

	int i = 1;
	long int j = 1;
	short sh = 1;
	char c  = 'a';
	float f = 3.0;
	double d = 7.0;

	pre_increment(i); // Ok
	pre_increment(sh); // Ok
	//pre_increment(c); // Expected error run-time assertion fail
	pre_increment(f); // Not Ok, as float is not an int
	//pre_increment(d); // Expected error run-time assertion fail

	better_pre_increment(i); // Ok
	//better_pre_increment(sh); // Not Ok as short is an int
	//better_pre_increment(c); // Expected error compile-time assertion fail
	//better_pre_increment(f); // Expected error compile-time assertion fail
	//better_pre_increment(d); // Expected error compile-time assertion fail

	smart_pre_increment(i); // OK
	smart_pre_increment(j); // OK
	smart_pre_increment(sh); // OK
	//smart_pre_increment(c); // Expected error compile-time assertion fail
	//smart_pre_increment(f); // Expected error compile-time assertion fail
	//smart_pre_increment(d); // Expected error compile-time assertion fail

	std::cout<<"End main\n";

	(void) c;
	(void) d;

	return 0;
}
