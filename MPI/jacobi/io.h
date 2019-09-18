/*
 * io.h
 *
 *  Created on: Sep 17, 2019
 *      Author: akadar
 */

#ifndef IO_H_
#define IO_H_

template<typename T>
void print_vec(const std::string& str, const T& vec){
	std::cout<<str;
	for(const auto& elem : vec) std::cout<<elem<<" ";
	std::cout<<"\n";
}

#endif /* IO_H_ */
