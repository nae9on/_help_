/*
 * c_style_string.cpp
 *
 *  Created on: May 22, 2019
 *      Author: akadar
 */

#include <iostream>

//int main()
int c_style_string()
{
	// All C-style strings are char arrays, but not all char arrays are C-style strings

	// Example 1
	char str1 = 'a';
	char str2[] = {'a','l','i'};
	std::cout<<str1<<"\n";
	std::cout<<*str2<<"\n";
	std::cout<<"--------------------\n";

	// Example 2
	const char* str3 = "ali";
	std::cout<<str3<<"\n";
	std::cout<<*(str3+3)<<"\n"; // prints NULL character
	std::cout<<"--------------------\n";

	// Example 3
	// Note: In ASCII, all upper case letters come before the lower case letters
	char a = 'A';
	std::cout<<static_cast<int>(a)<<"\n";
	std::cout<<static_cast<char>(97)<<"\n";
	std::cout<<"--------------------\n";

	std::cout<<std::endl;
	return 0;
}
