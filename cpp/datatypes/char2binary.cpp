/*
 * char2binary.cpp
 *
 *  Created on: 17 Apr 2020
 *      Author: ahkad
 */

#include <iostream>
#include <bitset>

int char2binary(){
	for(int i = 0; i<=128; ++i){
		signed char x = static_cast<signed char>(i), y;
		y = static_cast<signed char>(~x);
		y = static_cast<signed char>(y + static_cast<signed char>(1));
		std::cout<<i
				 <<"\t"
				 <<std::bitset<8>(x)
				 <<"\t"
				 <<std::bitset<8>(y)
				 <<"\t"
				 <<-i<<std::endl;
	}
	return 0;
}
