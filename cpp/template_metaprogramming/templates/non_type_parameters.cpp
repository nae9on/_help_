/*
 * non_type_parameters.cpp
 *
 *  Created on: July 25, 2019
 *      Author: akadar
 *
 * This example demonstrates template non-type parameters.
 *
 * template non-type parameters (tntp) are called as value template arguments
 * in the book "A tour of C++" by Bjarne Stroustrup.
 *
 * Permissible values of tntp are integral types (i.e. float, double etc are not allowed),
 * pointer types, enum types etc. Extensive list is available here
 * https://en.cppreference.com/w/cpp/language/template_parameters
 */

#include <iostream>

enum class X{};

template<typename T, int N> void f(){}
template<typename T, char N> void f(){}
// template<typename T, float N> void f(){} // Not allowed
template<typename T, float* fptr> void f(){}
template<typename T, X x> void f(){}

/*
 * Note the default's in the line below. For multiple template arguments,
 * all arguments after the first default must have default's.
 */

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
	T* data; // dynamic array is allocated on the heap
	char name[N]; // static array is allocated on the stack
};

int non_type_parameters()
{
	std::cout<<"In main\n";
	char string[5] {'a','b','c','d','e'};

	/*
	 * Note: A template value argument must be a constant expression, the reason
	 * being that non-constant expressions could change during run-time and therefore
	 * would require instantiation of a new template which is not possible during run-time
	 * because templates are compile time mechanisms.	 *
	 */
	buffer<int,5> vec2(10,string);
	buffer<int,6> vec3(10,string); // vec2 and vec3 are of different types.

	// Default used for value argument
	buffer<float> vec4(11,string);

	// error type/value mismatch, expected a type, got ‘5’
	//buffer<5> vec5(8,string);

	// default arguments used
	buffer<> vec6(12,string);
	// In the above, the bracket <> must be present but
	// can be left empty when default's are available

	// error missing template arguments.
	//buffer vec7(8,string);

	return 0;
}
