/*
 * calculate_sizeof_struct.cpp
 *
 *  Created on: Oct 11, 2019
 *      Author: akadar
 *
 * References:
 * [1] https://en.cppreference.com/w/cpp/language/sizeof
 * [2] https://stackoverflow.com/questions/119123
 * /why-isnt-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member
 */

#include <iostream>

struct W
{
    short s; // 2 bytes + 2 padding bytes
    int   i; // 4 bytes + 0 padding bytes
    char  c; // 1 bytes + 3 padding bytes
};

struct X
{
    int   i; // 4 bytes + 0 padding bytes
    char  c; // 1 bytes + 1 padding bytes
    short s; // 2 bytes + 0 padding bytes
};

struct Y
{
    char  c; // 1 bytes + 1 padding bytes
    short s; // 2 bytes + 0 padding bytes
    int   i; // 4 bytes + 0 padding bytes
};

struct Z
{
    int   i; // 4 bytes + 0 padding bytes
    short s; // 2 bytes + 0 padding bytes
    char  c; // 1 bytes + 1 padding bytes
};

struct Empty {};
struct Base { int a; };
struct Derived : Base { int b; };

int calculate_sizeof_struct()
{
	int x{1};
	int* itr = &x;

	int a[10];

    Empty e;
    Empty* ptr = &e;

    Derived d;
    Base& b = d;

    std::cout << "size of empty class:              " << sizeof(Empty)    << "\n"
    		  << "size of empty class object:       " << sizeof e        << "\n"
              << "size of empty class pointer:      " << sizeof ptr       << "\n"
			  << "size of int pointer:              " << sizeof itr       << "\n"
            //<< "size of function:                 " << sizeof(void())  << "\n" // error
            //<< "size of incomplete type:          " << sizeof(int[])   << "\n" // error
              << "size of array of 10 int:          " << sizeof a        << "\n"
              << "length of array of 10 int:        " << (sizeof a)/(sizeof a[0]) << "\n"
              << "size of the Derived:              " << sizeof d        << "\n"
              << "size of the Derived through Base: " << sizeof b        << "\n";


    /*
     * Note: Size of structures is affected by padding [2].
     * One can minimize the size of structures by sorting members by alignment
     * (sorting by size suffices for that in basic types). Ex struct Z above.
     */

    std::cout << "\n";
    std::cout << "size of W:                        " << sizeof(W)    << "\n";
    std::cout << "size of X:                        " << sizeof(X)    << "\n";
	std::cout << "size of Y:                        " << sizeof(Y)    << "\n";
	std::cout << "size of Z:                        " << sizeof(Z)    << "\n";

	return 0;
}
