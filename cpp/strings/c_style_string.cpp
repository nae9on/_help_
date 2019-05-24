/*
 * c_style_string.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>

/* The cstring header provides functions for dealing with C-style strings i.e.
 * null-terminated arrays of characters. This includes functions like strlen
 * and strcpy. It's the C++ version of the classic string.h header from C.
 */
#include <cstring>

//int main()
int c_style_string()
{
	/*
	 * A C-style string literal is a null-terminated array of char. A non-null
	 * terminated array of char is not a string literal. This implies that all
	 * C-style strings are char arrays, but not all char arrays are C-style strings
	 */

	// Examples

	// 1.
	// Behavior of strlen is not defined for non-null terminated array of char
	char char_array[3]{'x','y','z'};
	std::cout << strlen(char_array) << "\t" << char_array << std::endl;

	// 2.
	char string_literal[4]{'a','b','c','\0'};
	std::cout << strlen(string_literal) << "\t" << string_literal << std::endl;

	// 3.
	// A C-style string literal by definition is a const char*
	const char* also_string_literal = "I am C-style string literal";
	std::cout << strlen(also_string_literal) << "\t" << also_string_literal << std::endl;

	// 4.
	char str1 = 'a';
	char str2[] = {'a','l','i'};
	std::cout<<str1<<"\n";
	std::cout<<*str2<<"\n";
	std::cout<<"--------------------\n";

	// 5.
	const char* str3 = "ali";
	std::cout<<str3<<"\n";
	std::cout<<*(str3+3)<<"\n"; // prints NULL character
	std::cout<<"--------------------\n";

	// 6.
	// Note: In ASCII, all upper case letters come before the lower case letters
	char a = 'A';
	std::cout<<static_cast<int>(a)<<"\n";
	std::cout<<static_cast<char>(65)<<"\n";
	std::cout<<"--------------------\n";

	std::cout<<std::endl;
	return 0;
}
