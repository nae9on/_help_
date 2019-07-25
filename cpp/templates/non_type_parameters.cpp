/*
 * non_type_parameters.cpp
 *
 *  Created on: July 25, 2019
 *      Author: akadar
 */

#include <iostream>

/*
 * This script explains template non-type parameters.
 *
 * template non-type parameters (tntp) are called as value template arguments
 * in the book "A tour of C++" by Bjarne Stroustrup.
 *
 * A non-type template argument provided within a template argument list is
 * an expressionwhose value can be determined at compile time. Such arguments
 * must be constant expressions, addresses of functions or objects with external
 * linkage, or addresses of static class members.
 *
 * Permissible values of tntp are integral types (float, double, char etc are not allowed)
 * pointer to objects or functions, lvalue reference to object or functions, pointer to
 * class member functions, std::nullptr_t
 */

// Note the default arguments in the line below
template <typename T=double, unsigned N=5>
class buffer{
public:
	buffer(unsigned size_, char* name_): size{size_}, data{new T[size_]{}} {
		for (unsigned i=0; i<N; i++) name[i] = name_[i];
		for (unsigned i=0; i<size; i++) data[i] = i+1.5;
		out();
	}
	void out() const{
		std::cout<<"\nMy array of char is ";
		for (unsigned i=0; i<N; i++) std::cout<<name[i]<<" ";

		std::cout<<"\nMy data is ";
		for (unsigned i=0; i<size; i++)	std::cout<<data[i]<<" ";
	}
	~buffer(){
		delete[] data;
	}
private:
	unsigned size;
	T* data; // array is allocated on the heap
	char name[N]; // array is allocated on the stack
};

int main_non_type()
{
	std::cout<<"In main\n";
	char string[5] {'a','b','c','d','e'};

	/*
	 * Note: A template value argument must be a constant expression, the reason
	 * being that non-constant expressions could change during run-time and therefore
	 * would require instantiation of a new template which is not possible durin run-time
	 * because templates are compile time mechanisms.	 *
	 */
	buffer<int,5> vec2(10,string);
	buffer<int,6> vec3(10,string); // vec2 and vec3 are of different types.

	// Default value argument used
	buffer<float> vec4(11,string);

	// error type/value mismatch, expected a type, got ‘5’
	//buffer<5> vec5(8,string);

	// default arguments used
	buffer<> vec6(12,string);
	// In the above, the bracket <> must be present but
	// can be left empty when default arguments are available

	// error missing template arguments.
	//buffer vec7(8,string);

	return 0;
}
