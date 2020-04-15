/*
 * class_example.cpp
 *
 *  Created on: Aug 21, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=vs-2019
 * [2] http://www.cplusplus.com/reference/type_traits/is_literal_type/
 *
 */

#include <iostream>
#include <type_traits>

using my_int = unsigned long long int;

// Unlike const, constexpr can also be applied to class constructors. [1]

// Note: only a literal type can qualify as constexpr.
// A class is a literal-type under some conditions [2].

// X is not a literal-type since its constructor is not a constexpr.
class X{
public:
	X():n{5}{};
private:
	int n;
};

// Y is a literal type, but cannot be used with constexpr.
class Y{
public:
	constexpr Y():n{5}{};
private:
	mutable int n;
};

// Z is a literal type.
class Z{
public:
	constexpr Z():n{5}{};
	constexpr int get() const{
		return n;
	}
	void print() const{
		std::cout<<"n = "<<n;
	}
private:
	int n;
};

int class_example(){

	//constexpr X x; // Error X is not a literal-type
	const X x; // OK, run-time evaluation
	std::cout<<"Is X a literal-type? "<<std::is_literal_type<X>::value<<"\n";

	constexpr Y y; // OK
	std::cout<<"Is Y a literal-type? "<<std::is_literal_type<Y>::value<<"\n";
	//constexpr Y y1 = y; // Error y is not a constexpr

	constexpr Z f; // OK
	std::cout<<"Is Z a literal-type? "<<std::is_literal_type<Z>::value<<"\n";
    constexpr Z g = f; // OK f is a constexpr

	constexpr int n = g.get();
	g.print();

	(void) n;

	return 0;
}
