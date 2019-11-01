/*
 * csv2vec.cpp
 *
 *  Created on: 01 Nov 2019
 *      Author: ahkad
 *
 * Note: I have used istreambuf_iterator which never skips any characters (including whitespaces
 * such as '\n'). It grabs whatever 's next in the stream buffer unlike istream_iterator which
 * skips whitespaces. Also istream_iterator is useful when performing formatted input and is slower
 * than the istreambuf_iterator. Reference: Item 29, Effective STL, Scott Meyers.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename In, typename Out>
void csv2vec(In first, In last, Out& result) {
	std::string temp;
	unsigned i{0};
	while(1) {
		do{
			if(*first == '\n') break;
			temp.push_back(*first);
			++first;
		}while(*first != ',' && first != last);
		result[i].push_back(temp);
		if(*first == '\n') {
			++i;
			result.resize(i+1);
		}
		temp.clear();
		if(first == last) break;
		++first;
	}
}

int csv2vec(void) {
	std::vector<std::vector<std::string>> vec(1);
	std::ifstream in("data.txt");
	std::istream_iterator<char> begin(in);
	std::istream_iterator<char> end;
	csv2vec(begin,end,vec);

	for(const auto& vecouter : vec) {
		for(const auto& elem : vecouter){
			std::cout<<elem<<" ";
		}
		std::cout<<"\n";
	}
   return 0;
}
