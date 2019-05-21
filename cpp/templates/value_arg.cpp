/*
 * value_arg.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: akadar
 */

#include <iostream>

// Note the default arguments in the line below
// N is a value argument here
template <typename T=double, unsigned N=10>
class myVector{
private:
	unsigned size;
	T* data; // array is allocated on the heap
	char codeNdigit[N]; // array is allocated on the stack
public:
	myVector(unsigned _size, char* name): size{_size}, data{new T[_size]{}} {
		for (unsigned i=0; i<N; i++) codeNdigit[i] = name[i];
		for (unsigned i=0; i<size; i++) data[i] = i+1.5;
		out();
	}
	void out(){
		std::cout<<"My array of char is ";
		for (unsigned i=0; i<size; i++)
			std::cout<<codeNdigit[i]<<" ";
		std::cout<<std::endl;
		std::cout<<"My data is ";
		for (unsigned i=0; i<size; i++)
			std::cout<<data[i]<<" ";
		std::cout<<std::endl;
	}
};

int value_arg()
//int main()
{
	std::cout<<"In value_arg\n";
	char string[5] {'a','b','c','d','e'};

	// Normal usage
	myVector<int,5> vec2(10,string);

	// Default value argument used
	myVector<float> vec4(11,string);

	// error type/value mismatch, expected a type, got ‘4’
	//myVector<4> vec5(8,string);

	// default arguments used
	myVector<> vec6(12,string);
	// In the above, the bracket <> must be present but
	// can be left empty when default arguments are available

	// error missing template arguments.
	//myVector vec7(8,string);

	return 0;
}
