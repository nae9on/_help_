/*
 * myutils.h
 *
 *  Created on: 17 Apr 2020
 *      Author: ahkad
 */

#ifndef MYUTILS_H_
#define MYUTILS_H_

#include <iostream>
#include <bitset>
#include <cmath>
#include <iomanip>

void frac2bits(float f){
	for(int i=1; i<24; ++i){
		int x = static_cast<int>(2*f);
		if(f==0) break;
		f = 2*f - static_cast<float>(x);
		std::cout<<x;
	}
	std::cout<<"\n";
}

template <typename T>
void outbits(T x){

	using uchar = unsigned char;

	// point to all the bits as group of char's
	T* ptr{&x};
	char* ch = reinterpret_cast<char*>(ptr);

	// access all the bits
	constexpr int N = sizeof(T)/sizeof(char);
	std::bitset<N*CHAR_BIT> bits;
	for(uchar itr{0}, i=0; i<N; ++i){
		std::bitset<CHAR_BIT> b(*(ch+i));
		for(uchar j=0; j<CHAR_BIT; ++j)
			bits[itr++] = b[j];
	}

	// print bits in the right format
	for(int i=N*CHAR_BIT-1; i>=0; --i){ // taking into account endianness
		std::cout<<bits[i];
		if(std::is_integral<T>::value){
			if(i%4==0) std::cout<<" ";
		}
		if(std::is_floating_point<T>::value){
			if(i==N*CHAR_BIT-1) std::cout<<" ";
			switch(N){
			case 4: if(i==N*CHAR_BIT-9) std::cout<<" "; break;
			case 8: if(i==N*CHAR_BIT-12) std::cout<<" "; break;
		}
		}
	}

	std::cout<<std::endl;
}

template<typename T>
void out(T val){
	std::cout<<std::setprecision(15)<<val<<" = ";
	outbits<T>(val);
}

#endif /* MYUTILS_H_ */
