/*
 * with_templates.cpp
 *
 *  Created on: Aug 8, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <cmath>

using my_type = double;

template<unsigned e, typename T> double power(T t){
	return std::pow<T,unsigned>(t,e);
}

template<typename T, template<typename> class A, template<typename,typename> class C, typename Fptr>
void applyFunc(C<T,A<T>>& c, Fptr p){
	for(auto& elem : c){
		elem = (*p) (elem);
	}
}

int with_templates(){

	std::vector<my_type> x = {1.5,2.5,3.5};

	double (*square_ptr) (my_type) = &power<2,my_type>;
	double (*cube_ptr) (my_type) = &power<3,my_type>;

	std::cout<<(*square_ptr)(10)<<"\n";
	std::cout<<(*cube_ptr)(10)<<"\n";

	applyFunc(x,square_ptr);

	for(auto& elem : x){
		std::cout<<elem<<" ";
	}

	return 0;
}


