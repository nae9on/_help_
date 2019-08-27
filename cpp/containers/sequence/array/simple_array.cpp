/*
 * simple_array.cpp
 *
 *  Created on: Aug 27, 2019
 *      Author: akadar
 *
 * std::array vs plain C-style array
 * std::array is the simplest and was introduced in C++11. std::array container has some
 * advantages over a C-style array (int a[]). Its interface makes it more convenient to
 * find the size, and use with STL-style iterator-based algorithms. At the same time it
 * is equally fast. Note that std::array container allocates memory on the stack.
 * Reference: https://stackoverflow.com/questions/30263303/stdarray-vs-array-performance
 *
 * std::valarray vs std::array
 * std::valarray is the next simplest and was introduced in C++03. It is variable size
 * unlike array and has mathematical functions defined for numeric computation such as
 * +, -, cosine, sine etc. It also allows data slicing. std::valarray container allocates
 * memory on the heap like std::vector. *
 * Reference:
 * https://stackoverflow.com/questions/8965562/what-is-the-difference-between-stdvalarray-and-stdarray
 *
 * std::vector vs std::valarray
 * std::vector is even more convenient than std::valarray. std::vector is thought to be less
 * performant than std::valarray and std::array. However, the exact performance difference is
 * not clear.
 * Reference: https://stackoverflow.com/questions/1602451/c-valarray-vs-vector
 *
 */

#include <iostream>
#include <array>
#include <valarray>

int simple_array(){

	std::array<double,10> arr1;
	for (size_t i = 0; i<10; i++) arr1[i] = i;

	std::valarray<double> arr2;
	arr2.resize(10);
	for (size_t i = 0; i<10; i++) arr2[i] = i;
	arr2+=10;

	return 0;
}
