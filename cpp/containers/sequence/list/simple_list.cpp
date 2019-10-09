/*
 * simple_list.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: akadar
 *
 * References
 * [1] http://www.cplusplus.com/reference/list/list/
 */

#include <iostream>
#include <list>

#include <cassert>
#include <fstream>
#include <iterator>

int simple_list(){

	std::cout<<"In main simple_list.cpp\n";

	std::string file{"/home/akadar/git/_help_/cpp/containers/sequence/list/data.txt"};
	std::ifstream ifs{file};
	std::istream_iterator<int> dataBegin{ifs};
	std::istream_iterator<int> dataEnd;

	if(!ifs){
		assert(0 && "File does not exist");
	}

	std::list<int> data{dataBegin,dataEnd};
	for(const auto& elem : data) std::cout<<elem<<" ";
	std::cout<<"\n";

	std::list<int> adata{-1,-2,-3};

	// Move additional data to middle of data using splice member function (very special)
	std::list<int>::iterator pos{data.begin()};
	for(size_t i = 0; i<data.size()/2; ++i) ++pos; // list does not provide random-access-iterator!
	data.splice(pos,adata,adata.begin(),adata.end()); // Scott#4

	for(const auto& elem : data) std::cout<<elem<<" ";
	std::cout<<"\n";

	return 0;
}
