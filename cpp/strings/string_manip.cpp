/*
 * string_manip.cpp
 *
 *  Created on: Oct 12, 2019
 *      Author: akadar
 */

#include <iostream>
#include <string>
#include <algorithm> // std::equal

class icompare{
public:
	icompare() = default;
	bool operator()(const char& c1, const char&c2){
		bool flag = true;
		if(c1!=c2){
			if(std::toupper(c1)!=std::toupper(c2)){
				flag = false;
			}
		}
		return flag;
	}
};

int string_manip(){

	// case-insensitive comparison of two strings using STL and functor
	std::string str1{"I am fine"};
	std::string str2{"i aM fIne"};

	bool flag = false;
	if(str1.size()==str2.size())
		flag = std::equal(str1.cbegin(),str1.cend(),str2.cbegin(),icompare());

	if(flag)
		std::cout<<"Strings are equal\n";
	else
		std::cout<<"Strings are not equal\n";

	return 0;
}
