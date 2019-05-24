/*
 * std_string.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

// [1] https://embeddedartistry.com/blog/2017/7/24/stdstring-vs-c-strings
// [2] https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=vs-2019

#include <iostream>

// The string header provides the std::string class and related functions and operators.
#include <string>

//int std_string()
int main()
{
	/*
	 * Fundamentally std::string is similar to std::vector<char>
	 * std::string literals are also string literals but are more elaborate than C-style string literals
	 * All std::string stores is a pointer to the heap where all of it's data is stored.
	 */

	// Examples

	// 1.
	std::string std_string {"I am std string literal"};
	std::cout << std_string << " of length = " << std_string.size() << " and size = " << sizeof(std_string)<<" bytes"<<std::endl;

	// 2.
	// The const char* can be retrieved using the c_str or data method
	// This allows std::string to interoperate with C-string APIs
	const char* std_string_to_char = std_string.c_str();

	// 3.
	// std::strings have an overloaded + operator
	std::cout << std_string+" and I am defined in string header" << std::endl;

	// 4.
	// Easy assignment, copy, move etc
	std::string my_str {"Hello"};
	my_str = std::move(std_string);
	std::cout << "my_str = " << my_str << std::endl;
	std::cout << "std_string (post move): " << std_string << std::endl;
	my_str.clear();
	std::cout << "my_str (post-clear) = " << my_str << std::endl;
	std::cout << "my_str.empty() = " << my_str.empty() << std::endl;

	// Limitations of std::strings are listed here [1]

	// using namespace std::string_literals; // enables s-suffix for std::string literals [2]
	// Since C++14, string literal "s", can be used to convert a const char * to std::string
	// std::string std_string = "ali"s;

	return 0;
}
