/*
 * stl_algo_for_sorted_ranges.cpp
 *
 *  Created on: Oct 21, 2019
 *      Author: akadar
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric> // std::iota

int stl_algo_for_sorted_ranges(){

	std::deque<double> deq{1,2,3,3,3,3,3,4,5,6,7,8,9,10};

	std::random_shuffle(deq.begin(),deq.end());

	for(const auto& elem : deq) std::cout<<elem<<" ";

	std::cout<<"\n\n";

	std::sort(deq.begin(),deq.end(),std::greater<double>());

	for(const auto& elem : deq) std::cout<<elem<<" ";

	std::cout<<"\n\n";

	// binary_search (returns bool and not an iterator)
	double val{3.0};
	bool found = std::binary_search(deq.cbegin(),deq.cend(),val,std::greater<double>());
	if(found) std::cout<<"Element "<<val<<" found"<<"\n\n";

	// lower_bound (returns an iterator pointing to the first element not less than value)
	// upper_bound (returns an iterator pointing to the first element greater than value)
	auto it1 = std::lower_bound(deq.cbegin(),deq.cend(),0,std::greater<double>());

	if(it1==deq.cbegin()) std::cout<<"Pointing to cbegin\n\n";
	if(it1==deq.cend()) std::cout<<"Pointing to cend\n\n";
	if(it1!=deq.cend()) std::cout<<"Element["<<it1-deq.cbegin()<<"] = "<<*it1<<"\n\n";

	// equal_range
	auto pair = std::equal_range(deq.cbegin(),deq.cend(),val,std::greater<double>());
	if(pair.first!=pair.second)
			std::cout<<"Equal range for element "<<val<<" is ["<<pair.first-deq.cbegin()<<" "
			                            <<pair.second-deq.cbegin()<<")\n\n";

	// merge is trivial
	// inplace_merge is similar to merge except that merge occurs in the same container
	// without allocating memory for a new container to hold the merged result.

	return 0;
}
