/*
 * initializer_list.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: akadar
 *
 * References:
 * [1] http://www.cplusplus.com/reference/initializer_list/initializer_list/
 * [2] https://en.wikipedia.org/wiki/Most_vexing_parse
 */

#include <iostream>
#include <initializer_list>
#include <vector>

struct X{
	X(){
		std::cout<<"Default constructor called\n";
		rgb[0] = 0;
		rgb[1] = 0;
		rgb[2] = 0;
	}
	explicit X(std::initializer_list<unsigned char> rgb_){
		std::cout<<"Constructor with std::initializer_list parameter called\n";
		int i{0};
		for (const auto& e: rgb_){
			rgb[i++] = e;
		}
	}
	void out(){
		std::cout<<static_cast<int>(rgb[0])
				<<"\t"<<static_cast<int>(rgb[1])
				<<"\t"<<static_cast<int>(rgb[2])<<"\n";
	}
	unsigned char rgb[3];
};

template<typename T> void show_list(std::initializer_list<T> l){
	// range-for supported
	for(const auto& elem : l) std::cout<<elem<<"\t";
	std::cout<<"\n";
}

struct Y{
	Y():y{0}{}
	Y(int y_): y{y_}{
		std::cout<<"Ordinary constructor of Y called\n";
	}
	int y;
};

struct Z{
	Z(Y y_) {
		y = y_;
	}
	void out(){}
	Y y;
};

int main(){

	/*
	 * An object of type std::initializer_list<T> is a lightweight proxy object that
	 * provides access to an array of objects of type const T.
	 */
	std::initializer_list<int> l1 = {10,20,30};

	// Copying a std::initializer_list does not copy the underlying objects.
    auto l2 = l1; // reference semantics and no actual copy
    show_list(l2);

    // In the example below, a std::initializer_list object is also automatically constructed.
    show_list({100,200,300});

	// Call to the default constructor
    X x1;
	x1.out();

	/*
	 * In the example below, a std::initializer_list object is automatically constructed
	 * when a braced-init-list is used to list-initialize an object, where the corresponding
	 * constructor accepts an std::initializer_list parameter.
	 */
	X x2({10,11,12});
	x2.out();

	// Works the same as above!
	X x3 {101,101,102};
	x3.out();

	// Note that the ordinary constructor of Y gets called here.
	Y y1{7};

	std::vector<int> vec1(10); // a vector of length 10
	std::vector<int> vec2{10}; // Surprise a vector of length 1 with elem 10

	// Some advantages of using std::initializer_list

    // 1. Warning on narrowing conversions
	// std::initializer_list<int> l3 = {10.5,20.5,30.5}; // Warning

	// 2. Resolves the most vexing parse problem [2]
	//Z z(Y()); z.out(); // Error Z z(Y()) is interpreted as function declaration by the compiler.
	Z z{Y()}; z.out();

	return 0;
}
