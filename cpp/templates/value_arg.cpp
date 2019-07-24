/*
 * value_arg.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: akadar
 */

#include <iostream>

// Note the default arguments in the line below
// N is a value argument here
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

int main_value_arg()
{
	std::cout<<"In main\n";
	char string[5] {'a','b','c','d','e'};

	// Note: A template value argument must be a constant expression
	buffer<int,5> vec2(10,string);

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
