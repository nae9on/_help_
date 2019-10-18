/*
 * sorted_index.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: akadar
 */

#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <numeric> // std::iota

template<typename T, typename A, template<typename,typename> class C>
std::vector<size_t> sorted_index(const C<T,A>& v, std::string order = "asc"){

	std::vector<size_t> index;
	index.resize(v.size());
	std::iota(index.begin(),index.end(),0);
	if(order.compare("asc")==0)
		std::sort(index.begin(),index.end(),[&](const T& lhs, const T& rhs)->bool{return v[lhs]<v[rhs];});
	else if(order.compare("desc")==0)
		std::sort(index.begin(),index.end(),[&](const T& lhs, const T& rhs)->bool{return v[lhs]>v[rhs];});
	return index;
}

int sorted_index(){

	std::vector<int> x{8,3,9,1,2,5,6,4,10,7};

	std::vector<size_t> index = sorted_index(x,"desc");

	for(const auto& elem : index) std::cout<<elem<<" ";

	std::cout<<"\n";

	return 0;
}
