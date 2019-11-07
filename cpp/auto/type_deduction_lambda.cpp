/*
 * type_deduction_lambda.cpp
 *
 *  Created on: 07 Nov 2019
 *      Author: ahkad
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

class X{
public:
	X(){
		x = count;
		++count;
	}
	int x;
	static size_t count;
};

size_t X::count = 1;

int type_deduction_lambda(){

	// prepare
	std::vector<X> vec(10);
	std::random_shuffle(vec.begin(),vec.end());
	for(const auto& elem : vec) std::cout<<elem.x<<" ";
	std::cout<<"\n";

	// sort using lambda

	// solution without using auto
	//std::function<bool(const X& e1, const X& e2)> lmb = [](const X& e1, const X& e2){return e1.x<e2.x;};

	//auto lmb = [](const X& e1, const X& e2){return e1.x<e2.x;}; // c++11

	// use of 'auto' in lambda parameter declaration only available with -std=c++14
	auto lmb = [](const auto& e1, const auto& e2){return e1.x<e2.x;}; // c++14

	std::cout<<"Type lmb is "<<type_id_with_cvr<decltype(lmb)>().pretty_name()<<"\n";

	std::sort(vec.begin(),vec.end(),lmb);
	for(const auto& elem : vec) std::cout<<elem.x<<" ";

	return 0;
}
