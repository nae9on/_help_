/*
 * basic_out.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: akadar
 */

#include <iostream> // for default output stream object std:cout
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

template<typename C, typename F, typename T = typename C::value_type>
void write_data(C& c, F& ofs){

	ofs<<std::scientific; // this manipulator will stick

	std::string delimiter{"\n"};

	std::ostream_iterator<T> begin(ofs,delimiter.c_str());

	std::copy(c.cbegin(), c.cend(), begin);

	// how to pass a manipulator that won't stick? using Boost?
}

int basic_out(){

	std::ofstream ofs("data.txt", std::ofstream::out | std::ofstream::ate); // use ::app for append

	if(!ofs){
		throw std::invalid_argument("file does not exist");
	}

	std::vector<double> x{1,2,3,100};

	std::vector<std::string> s{"I","am", "cpp"};

	write_data(x,std::cout); // passing the default output stream object std:cout
	write_data(s,ofs); // passing the ofs stream object attached to "data.txt"

	return 0;
}
