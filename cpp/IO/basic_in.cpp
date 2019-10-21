/*
 * basic_in.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: akadar
 */

#include <iostream> // for default input stream object std:cin
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

template<typename C, typename F, typename T = typename C::value_type>
void read(C& c, F& ifs){

	std::istream_iterator<T> begin(ifs), end{};

	std::copy(begin, end, std::back_inserter(c));
}

int basic_in(){

	std::ifstream ifs("data.txt");

	if(!ifs){
		throw std::invalid_argument("file does not exist");
	}

	std::vector<std::string> x;

	read(x,ifs);

	for(const auto& elem : x) std::cout << elem << "\n";

	return 0;
}
