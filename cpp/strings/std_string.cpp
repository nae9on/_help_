/*
 * std_string.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

// [1] https://embeddedartistry.com/blog/2017/7/24/stdstring-vs-c-strings

#include <iostream>

/* The cstring header provides functions for dealing with C-style strings i.e.
 * null-terminated arrays of characters. This includes functions like strlen
 * and strcpy. It's the C++ version of the classic string.h header from C.
 */
#include <cstring>

// The string header provides the std::string class and related functions and operators.
#include <string>

//int std_string()
int main()
{
	// Fundamentally std::string is similar to std::vector<char>

	using namespace std::string_literals;

	// A non-null terminated array of characters is not a string literal
	// and therefore the behavior of strlen is not defined
	char char_array[3]{'a','l','i'};
	std::cout << strlen(char_array) << "\t" << char_array << std::endl;

	// A null terminated array of characters is a string literal
	char string_literal[4]{'a','l','i','\0'};
	std::cout << strlen(string_literal) << "\t" << string_literal << std::endl;

	// An array of characters enclosed in double quotes is a string literal
	const char* also_string_literal = "ali"; // Assigning a string constant to a const char*
	std::cout << strlen(also_string_literal) << "\t" << also_string_literal << std::endl;

	// Since C++14, string literal "s", can be used to convert a const char * to std::string
	std::string std_string = "ali"s;
	std::cout << std_string.size() << "\t" << std_string << std::endl;

	// The const char* can be retrieved back using the c_str or data method
	// This allows std::string to interoperate with C-string APIs
	const char* std_string_to_char = std_string.c_str();

	// std::strings have an overloaded + operator
	std::cout << std_string+std_string << std::endl;

	// Easy assignment, copy, move etc
	std::string my_str = "Hello";
	my_str = std::move(std_string);
	std::cout << "my_str (post move): " << my_str << std::endl;
	std::cout << "std_string (post move): " << std_string << std::endl;

	my_str.clear();
	std::cout << "my_str (post-clear): " << my_str << std::endl;
	std::cout << "my_str.empty(): " << my_str.empty() << std::endl;

	// Limitations of std::strings are listed here [1]

	return 0;
}
