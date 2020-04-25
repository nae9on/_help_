/*
 * std_string.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 *
 *  References:
 *  [1] https://embeddedartistry.com/blog/2017/7/24/stdstring-vs-c-strings
 *  [2] https://docs.microsoft.com/en-us/cpp/cpp/string-and-character-literals-cpp?view=vs-2019
 *  [3] Effective STL - Scott Meyers, Item 15
 *
 */

#include <iostream>

// The string header provides the std::string class and related functions and operators.
#include <string>

using namespace std::string_literals; // enables s-suffix for std::string literals (C++14 onwards)

int std_string()
{
	/*
	 * Note:
	 * 1. Fundamentally std::string is similar to std::vector<char>. A std::string object stores a
	 * pointer to the heap where all of it's data is stored. Its implementation varies across
     * different stdlib implementations[3] and its size is either 1 byte (assuming sizeof(char*)=1)
     * or b>=7 bytes. Therefore, be aware of different string implementation[3].
	 * 2. The data for strings is not guaranteed to be stored in a single chunk of contiguous
	 * memory.
	 * 3. Its internal representation is not guaranteed to end with a null character.
	 * 4. There are some limitations of std::strings as listed here [1]
	 */

	// Example 1.
	std::string std_string {"I am std string literal"};
	std::cout << std_string << " of length = " << std_string.size()
	        << " and size = " << sizeof(std_string)<<" bytes"<<std::endl;

	// Example 2.
	// The const char* can be retrieved using the c_str or data method
	// This allows std::string to interoperate with C-string APIs
	// This is very important considering points 1 and 2 above.
	const char* std_string_to_char = std_string.c_str();
	std::cout<<std_string_to_char<<"\n";

	// Example 3.
	// std::string literals are also string literals but are more elaborate than C-style string
    // for example they define an overloaded + operator
	std::cout << std_string+" and I am defined in string header" << std::endl;

	// Example 4.
	// Easy assignment, copy, move etc
	std::string my_str {"Hello"};
	my_str = std::move(std_string);
	std::cout << "my_str = " << my_str << std::endl;
	std::cout << "std_string (post move): " << std_string << std::endl;
	my_str.clear();
	std::cout << "my_str (post-clear) = " << my_str << std::endl;
	std::cout << "my_str.empty() = " << my_str.empty() << std::endl;

	// Example 5.
	// Since C++14, using namespace std::string_literals enables s-suffix for std::string literals [2]
	// auto str = "ali"; // type deduced as char const*
	// auto str = "ali"s; // type deduced as std::string

    std::string s1{"abc\0\0def"}; // string terminated at Null
    std::string s2{"abc\0\0def"s}; // string not terminated at Null
    std::string s3{R"(abc\0\0def)"s}; // string not terminated at Null and in raw form
    std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n";
    std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n";
    std::cout << "s3: " << s3.size() << " \"" << s3 << "\"\n";

	return 0;
}
