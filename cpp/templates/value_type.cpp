/*
 * value_type.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>

// simple example without using templates
using container1 = std::vector<double>;
container1::value_type agreegate1(const container1& c, container1::value_type init) {
	container1::value_type sum = init;
	for(const auto& e:c) sum+=e;
	return sum;
}

// example using templates
template<typename t> using container2 = std::vector<t>;
template<typename z>
typename z::value_type agreegate2(const z& c, typename z::value_type init) {
	typename z::value_type sum = init;
	for(const auto& e:c) sum+=e;
	return sum;
}

int main_value_type(){
	container1 c1{1.5,2.5,3.5};
	std::cout<<"Sum = "<<agreegate1(c1,100)<<"\n";

	container2<int> c2{1,2,3};
	std::cout<<"Sum = "<<agreegate2<container2<int>>(c2,100)<<"\n";

	// Note the automatic type deduction for function templates
	container2<int> c3{10,20,30};
	std::cout<<"Sum = "<<agreegate2(c3,100)<<"\n";
	return 0;
}
