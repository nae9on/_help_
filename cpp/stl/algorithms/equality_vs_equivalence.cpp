/*
 * equality_vs_equivalence.cpp
 *
 *  Created on: Oct 14, 2019
 *      Author: akadar
 *
 * Example to illustrate difference between equality and equivalence.
 * Equality is defined by the == operator (applies to sequence containers)
 * Equivalence is defined by a comparison function (default <)  (applies to associative containers)
 *
 * This example also illustrates that care must be taken when using std::algorithms for associative
 * containers. Prefer member function over algorithms for associative containers. Scott#44
 *
 * References:
 * Scott#19
 *
 */

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

class char_icompare{
public:
	char_icompare() = default;
	bool operator()(const char& c1, const char&c2) const{
		if(std::toupper(c1)!=std::toupper(c2))
			return c1<c2;
		else
			return false;
	}
};

class str_icompare{
public:
	str_icompare() = default;
	template<typename T>
	bool operator()(T& str1, T& str2)const {
		bool less_than = false;

		auto it1 = str1.cbegin();
		char_icompare comp;
		for(auto it2 = str2.cbegin(); it2!=str2.cend(), it1!=str1.cend(); ++it2, ++it1){
			less_than = comp(*it1,*it2);
			if(less_than) break;
		}

		if(str1.length()!=str2.length())
			less_than = str1.length()<str2.length();

		return less_than;
	}
};

int equality_vs_equivalence(){

	std::string s1{"xyZ"}, s2{"XYZ"}, s3{"xYz"}, s4{"xyZpo"};
	std::cout<<"String compare = "<<s1.compare(s2)<<"\n"; // s1>s2 as 'x'=97 and 'X'=65 in ASCII

	std::set<std::string,std::less<std::string>> csm; // case-sensitive-map
	csm.insert(s1);
	csm.insert(s2);
	csm.insert(s3);
	csm.insert(s4);

	for(const auto& elem : csm) std::cout<<elem<<"\n";

	if(std::find(csm.begin(),csm.end(),s3)!=csm.end()) // note that std::find won't work for map
		std::cout<<s3<<" found in csm!"<<"\n";

	std::cout<<"\n";

	// s1, s2 and s3 are equivalent according to str_icompare but not equal of-course
	std::set<std::string,str_icompare> cism; // case-insensitive-map
	cism.insert(s1);
	cism.insert(s2);
	cism.insert(s3);
	cism.insert(s4);

	for(const auto& elem : cism) std::cout<<elem<<"\n";

	if(std::find(cism.begin(),cism.end(),s3)==cism.end())
		std::cout<<s3<<" not found in cism!"<<"\n";

	return 0;
}
